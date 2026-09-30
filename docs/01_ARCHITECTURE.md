# 01 — ARCHITECTURE

> Chỉ Tier A và chủ dự án được sửa file này.

## 1. Nguyên tắc phân vai
| Lớp | Dùng cho |
|---|---|
| C++ | Hệ thống, base class, logic cần hiệu năng/đúng đắn (GAS, damage, trace, AI task, save) |
| Blueprint | Kết hợp component, gắn asset, tuning giá trị, ability cụ thể đơn giản |
| Data Asset / Data Table | Số liệu: vũ khí, đòn đánh, enemy, boss, item |
| AnimNotify / NotifyState | Thời điểm (trace on/off, i-frame, combo window) — **không hardcode thời gian trong code** |

## 2. Module (ADR-001)
```
Unreal/Source/
├── Eclipse.Target.cs
├── EclipseEditor.Target.cs
└── Eclipse/
    ├── Eclipse.Build.cs
    ├── Eclipse.h / Eclipse.cpp
    ├── Core/          # interface, types, tags, event subsystem, utilities — KHÔNG phụ thuộc thư mục nào khác
    ├── Abilities/     # ASC, AttributeSets, ability base, execution calc, effects C++
    ├── Combat/        # CombatComponent, weapon, trace, attack data, input buffer, notifies
    ├── Characters/    # CharacterBase, Player, Enemy, Boss, PlayerController, LockOn
    ├── AI/            # AIController, StateTree tasks/conditions/evaluators, EQS
    ├── Inventory/     # item/weapon definitions, inventory & equipment components
    ├── World/         # rest point, fog gate, interactables, pickups, world state
    ├── Save/          # SaveGame, save subsystem
    └── UI/            # widget base C++, HUD view models
```
Mỗi thư mục có `Public/`-style header ngay cạnh `.cpp` (đơn giản hoá; một module nên không cần tách Public/Private).

## 3. Quy tắc include (bắt buộc — review sẽ kiểm tra)
| Thư mục | Được include |
|---|---|
| `Core/` | chỉ engine |
| `Abilities/` | Core |
| `Combat/` | Core, Abilities |
| `Inventory/` | Core, Abilities, Combat (chỉ Combat/Data) |
| `Characters/` | Core, Abilities, Combat, Inventory |
| `AI/` | Core, Abilities, Combat, Characters |
| `World/`, `Save/` | Core, Abilities (qua interface; **không** include Characters) |
| `UI/` | tất cả (chỉ đọc) |
| **Không ai** | include `UI/` |

Cần gọi ngược chiều → dùng interface trong `Core/` hoặc event.

## 4. Class hierarchy
```
ACharacter
└── AEclipseCharacterBase            (abstract)   IAbilitySystemInterface, IEclipseDamageable, IEclipseTargetable
    ├── AEclipsePlayerCharacter
    ├── AEclipseEnemyCharacter
    │   └── AEclipseBossCharacter
    └── AEclipseNPCCharacter          (sau Vertical Slice)

AActor
├── AEclipseWeapon (abstract)
│   └── AEclipseMeleeWeapon           (mọi kiếm/giáo/búa — phân biệt bằng data, ADR-004)
├── AEclipseRestPoint
├── AEclipseFogGate
├── AEclipsePickup
└── AEclipseSoulsDrop

APlayerController → AEclipsePlayerController   (Enhanced Input, HUD)
AAIController     → AEclipseAIController       (Perception, StateTree component)
AGameModeBase     → AEclipseGameMode
UGameInstance     → UEclipseGameInstance
```

## 5. Component
**AEclipseCharacterBase** (mọi character):
| Component | Vai trò |
|---|---|
| `UAbilitySystemComponent` (`UEclipseAbilitySystemComponent`) | abilities, effects, tags |
| `UEclipseCombatAttributeSet` (subobject, không phải component) | Health, Stamina, Poise + meta attribute |
| `UEclipseCombatComponent` | vũ khí hiện tại, weapon trace, combo state, gửi damage |
| `UEclipseEquipmentComponent` | slot trang bị, spawn/attach weapon actor, grant ability từ vũ khí |

**AEclipsePlayerCharacter** thêm: `USpringArmComponent`, `UCameraComponent`, `UEclipseLockOnComponent`, `UEclipseInputBufferComponent`, `UEclipseInteractionComponent`, `UEclipseInventoryComponent`.

**AEclipseEnemyCharacter** thêm: `UEclipseEnemyDataComponent` (tham chiếu `DA_Enemy_*`, loot, souls reward). Aggro nằm trong StateTree/Perception, không cần component riêng.

**AEclipseBossCharacter** thêm: `UEclipseBossPhaseComponent`.

## 6. Interfaces (`Core/`)
```cpp
IEclipseDamageable   // bool CanBeDamaged(const FEclipseDamageContext&) const; ...
IEclipseTargetable   // bool IsTargetable() const; FVector GetTargetLocation() const;
IEclipseInteractable // FText GetPrompt() const; void Interact(AActor* Instigator);
IEclipseSaveable     // FGuid GetSaveId() const; void WriteSave(FEclipseActorSaveData&); void ReadSave(const FEclipseActorSaveData&);
```
Damage thật sự luôn đi qua GAS (GameplayEffect + ExecutionCalculation). `IEclipseDamageable` chỉ để hỏi "có nhận damage được không" và cho actor không có ASC (thùng gỗ) phản hồi.

## 7. Event (ADR-011)
```cpp
// Core/EclipseEventSubsystem.h
UCLASS() class UEclipseEventSubsystem : public UGameInstanceSubsystem
{
    // Broadcast(FGameplayTag Channel, const FInstancedStruct& Payload)
    // Listen(FGameplayTag Channel, delegate) -> FEclipseEventHandle
};
```
Kênh ví dụ: `Event.Boss.Defeated`, `Event.Player.Died`, `Event.Player.Rested`, `Event.World.ShortcutOpened`, `Event.Item.Acquired`.

## 8. Data Assets (Primary Asset Types — đăng ký trong Asset Manager)
| Class | Asset ví dụ |
|---|---|
| `UEclipseWeaponDefinition` | `DA_Weapon_GreatSword_Iron` |
| `UEclipseAttackDefinition` | `DA_Attack_GreatSword_Light01` |
| `UEclipseItemDefinition` | `DA_Item_Flask_Health` |
| `UEclipseEnemyDefinition` | `DA_Enemy_Hollow_Sword` |
| `UEclipseBossDefinition` | `DA_Boss_Warden` |
| `UEclipseArmorDefinition` | (M7) |

## 9. Save (M4)
- `UEclipseSaveGame` chứa `FEclipsePlayerSave` + `TMap<FGuid, FEclipseActorSaveData>` + `FGameplayTagContainer WorldFlags`.
- Actor đặt trong level: dùng một `FGuid SaveId` UPROPERTY do con người/Editor tạo (không dùng tên actor, không dùng pointer).
- Rest point / chết → ghi save. Không autosave mỗi frame.

## 10. Plugin bật ở M0
`GameplayAbilities`, `EnhancedInput`, `PoseSearch`, `MotionWarping`, `Chooser` (GASP cần), `AnimationWarping`, `StateTree`, `GameplayStateTree`, `Niagara` (mặc định bật), `StructUtils` (nếu 5.8 chưa gộp vào engine — kiểm tra ở T-003).
Không bật: PCG, Mass*, SmartObjects, World Partition cho level chính (dùng level thường ở giai đoạn slice).
