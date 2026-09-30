# 04 — COMBAT & GAS SPEC

> Spec cho M1–M2. Tier A sở hữu. Số liệu trong file này là **giá trị khởi đầu để tuning**, không phải thiết kế cuối.

## 1. Luồng một đòn đánh
```
Input (IA_LightAttack)
  → UEclipseInputBufferComponent (lưu input ~0.25s)
  → TryActivateAbility(Ability.Attack.Light)   [nếu không bị block; nếu bị block → nằm trong buffer chờ Window]
  → GA_Attack (C++ base: UEclipseGameplayAbility_Attack)
      đọc UEclipseAttackDefinition hiện tại từ CombatComponent (combo index)
      commit cost (Stamina)
      PlayMontageAndWait(AttackDef.Montage)
  → Montage notifies:
      ANS_WeaponTrace      → CombatComponent bật sweep trace
      ANS_ComboWindow      → thêm tag Window.Combo  (buffer có Light → chain đòn kế)
      ANS_CancelWindow     → thêm tag Window.Cancel (buffer có Dodge → huỷ đòn)
      AN_HitStopAllowed ...
  → Hit → CombatComponent tạo FGameplayEffectSpec(GE_Damage) với SetByCaller:
          Data.Damage.Physical, Data.Damage.Poise, ...
  → Apply lên ASC của target → UEclipseDamageExecution tính damage cuối
  → AttributeSet PostGameplayEffectExecute: trừ Health / Poise
      Poise ≤ 0  → gửi GameplayEvent Event.HitReact.Stagger
      Health ≤ 0 → gửi GameplayEvent Event.Death
      còn lại    → Event.HitReact.Light
  → GA_HitReact / GA_Death (kích hoạt bằng Gameplay Event trigger)
  → GameplayCue GC_Hit_* (VFX + SFX + camera shake) + hitstop
```

## 2. Gameplay Tags (native — `EclipseGameplayTags`)
```
State.Attacking  State.Dodging  State.Blocking  State.Parrying
State.Staggered  State.HitReact  State.Dead  State.Invulnerable  State.Sprinting  State.Resting

Window.Combo  Window.Cancel  Window.Parry  Window.Invulnerable

Ability.Attack.Light  Ability.Attack.Heavy  Ability.Attack.Sprint  Ability.Attack.Riposte
Ability.Dodge  Ability.Block  Ability.Parry  Ability.Sprint  Ability.UseItem  Ability.HitReact  Ability.Death

Event.HitReact.Light  Event.HitReact.Heavy  Event.HitReact.Stagger  Event.Death  Event.Parried
Event.Boss.Defeated  Event.Player.Died  Event.Player.Rested  Event.World.ShortcutOpened  Event.Item.Acquired

Data.Damage.Physical  Data.Damage.Fire  Data.Damage.Magic  Data.Damage.Poise  Data.Cost.Stamina

Weapon.Type.StraightSword  Weapon.Type.GreatSword  Weapon.Type.Spear  Weapon.Type.Shield
Status.Poison  Status.Bleed  (sau M4)

GameplayCue.Hit.Flesh  GameplayCue.Hit.Armor  GameplayCue.Block  GameplayCue.Parry
```

## 3. Ability activation rules
| Ability | Blocked by | Cancel khi kích hoạt | Ghi chú |
|---|---|---|---|
| Attack.Light | State.Dead, State.Staggered, State.HitReact, State.Dodging | — | Khi State.Attacking: chỉ chạy nếu có `Window.Combo` (từ buffer) |
| Attack.Heavy | như trên | — | chain từ light trong Window.Combo được |
| Dodge | State.Dead, State.Staggered, State.HitReact | Ability.Attack.*, Ability.Block (chỉ khi có `Window.Cancel`) | cần Stamina > 0 |
| Block | State.Dead, State.Staggered, State.Attacking, State.Dodging | — | giữ nút |
| Parry | như Block | — | Window.Parry từ ANS |
| UseItem | State.Dead, State.Attacking, State.Dodging, State.HitReact | — | |
| HitReact | State.Dead, State.Invulnerable | Attack, Block, UseItem | trigger bởi event |
| Death | — | tất cả | trigger bởi event |

Không có stamina: **cho phép** bắt đầu đòn/dodge khi Stamina > 0 (kể cả nhỏ hơn cost) → Stamina về âm nhẹ/0, giống Dark Souls. Stamina = 0 → không được.

## 4. Input buffer
- Một slot, lưu `(InputTag, Timestamp)`. Input mới ghi đè input cũ.
- Hết hạn sau `BufferDuration = 0.25s` (tunable).
- Mỗi khi tag `Window.Combo` / `Window.Cancel` được thêm, hoặc một ability kết thúc → thử kích hoạt input đang buffer.
- Dodge và Attack đều đi qua buffer. Block (giữ) thì không.

## 5. Attributes — `UEclipseCombatAttributeSet`
| Attribute | Khởi đầu (player) | Ghi chú |
|---|---|---|
| Health / MaxHealth | 400 / 400 | |
| Stamina / MaxStamina | 100 / 100 | regen 45/s, delay 0.6s sau khi tiêu (GE periodic + tag chặn) |
| Poise / MaxPoise | 30 / 30 | reset về Max sau 3s không bị đánh |
| IncomingDamage (meta) | — | không lưu, dùng trong Execution |
| IncomingPoiseDamage (meta) | — | |

`UEclipseDefenseAttributeSet` (M2 cuối): PhysicalAbsorption, FireAbsorption, MagicAbsorption (0–1).
Primary stats (Vitality, Endurance, Strength, Dexterity) → M7, tính ra Max* qua GE infinite + MMC.

## 6. Damage execution
```
Raw = SetByCaller(Data.Damage.Physical) * AttackDef.MotionValue
Final = Raw * (1 - PhysicalAbsorption)
if target State.Blocking và đòn từ phía trước: Final *= (1 - Shield.BlockAbsorption); trừ Stamina = Raw * Shield.StaminaDamageRatio
Poise tương tự, block không giảm poise damage lên stamina mà thay bằng guard break khi Stamina ≤ 0
Parry thành công (Window.Parry đang mở): không damage, attacker nhận Event.Parried → stagger đặc biệt → mở riposte
```

## 7. Attack Definition — `UEclipseAttackDefinition`
| Field | Kiểu | Ví dụ |
|---|---|---|
| Montage | `TSoftObjectPtr<UAnimMontage>` | AM_GS_Light01 |
| AttackTag | FGameplayTag | Ability.Attack.Light |
| MotionValue | float | 1.0 |
| PoiseDamage | float | 34 |
| StaminaCost | float | 18 |
| HitReactStrength | enum Light/Heavy | Heavy |
| NextComboAttack | `TObjectPtr<UEclipseAttackDefinition>` | DA_Attack_GS_Light02 |
| bUseMotionWarping | bool | true |
| WarpMaxDistance | float | 150 |
| HitStopDuration | float | 0.06 |
Base damage lấy từ `UEclipseWeaponDefinition`, nhân MotionValue của đòn.

## 8. Weapon trace (ADR-013)
- Socket trên mesh vũ khí: `Trace_Start`, `Trace_End` (+ tuỳ chọn `Trace_Mid`).
- Mỗi tick khi trace bật: sweep sphere (bán kính theo vũ khí) từ vị trí socket frame trước đến frame này; nếu góc xoay lớn thì chia sub-step (≥ 3).
- `TSet<TWeakObjectPtr<AActor>> HitActorsThisSwing` reset khi ANS_WeaponTrace bắt đầu.
- Trace channel riêng: `ECC_EclipseWeapon` (khai báo trong DefaultEngine.ini — Tier A).
- Debug: CVar `eclipse.Combat.DrawTraces 1`.

## 9. Dodge
- GA_Dodge: cost 20 Stamina, montage theo hướng input (roll F/B/L/R; khi không lock-on chỉ roll theo hướng input).
- `ANS_Invulnerable` thêm `State.Invulnerable` ~0.10s → 0.42s (giá trị ở montage, không ở code).
- Root motion bật.

## 10. Hitstop & feel
- Hitstop: giảm `CustomTimeDilation` của attacker và target xuống 0.05 trong `HitStopDuration`.
- Camera shake nhẹ theo HitReactStrength.
- Mỗi hit có GameplayCue.

## 11. Lock-on — `UEclipseLockOnComponent`
- FindTargets: overlap sphere 1500cm, lọc `IEclipseTargetable::IsTargetable()`, line of sight.
- Score = w_dist*(1 - d/Max) + w_center*(dot với camera forward) + w_visible. Trọng số là UPROPERTY.
- Switch: dùng hướng stick phải/chuột trong screen space, chọn target gần nhất theo hướng đó.
- Mất target khi: xa > 2000cm, mất LOS > 1.5s, target chết.
- Khi lock-on: character strafe (orient to target), camera nội suy nhìn giữa player và target.
