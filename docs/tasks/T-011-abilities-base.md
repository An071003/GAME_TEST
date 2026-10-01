# T-011 — `Abilities/`: ASC, CombatAttributeSet, GameplayAbility base

| | |
|---|---|
| Status | TODO |
| Milestone | M1 |
| Tier | A |
| Gợi ý model | Opus 5.5 (GPT 6.1 review chéo AttributeSet) |
| Phụ thuộc | T-010 |
| Branch | `task/T-011-abilities-base` |

## Mục tiêu
Nền GAS theo ADR-002/005: ASC đặt trên Character, AttributeSet Health/Stamina/Poise + meta attribute, ability base class mà mọi `GA_*` kế thừa.

## Đọc trước
- `docs/04_COMBAT_GAS_SPEC.md` §1, §3, §5; `docs/01_ARCHITECTURE.md` §5
- `docs/DECISIONS.md` ADR-002, ADR-003, ADR-005, ADR-012

## Được phép sửa / tạo
- `Unreal/Source/Eclipse/Abilities/EclipseAbilitySystemComponent.h/.cpp`
- `Unreal/Source/Eclipse/Abilities/EclipseCombatAttributeSet.h/.cpp`
- `Unreal/Source/Eclipse/Abilities/EclipseGameplayAbility.h/.cpp`
- `Unreal/Source/Eclipse/Tests/EclipseAttributeSetTest.cpp`
- Xoá `Abilities/.gitkeep`

## Thiết kế
- ASC: không cấu hình replication / prediction (ADR-005); helper `AbilityInputTagPressed/Released(FGameplayTag)` để input buffer (M2) và controller (T-012) gọi qua tag thay vì InputID.
- AttributeSet: Health/MaxHealth, Stamina/MaxStamina, Poise/MaxPoise, meta `IncomingDamage`, `IncomingPoiseDamage`. Clamp trong `PreAttributeChange` + `PostGameplayEffectExecute`. Health ≤ 0 → GameplayEvent `Event.Death`; Poise ≤ 0 → `Event.HitReact.Stagger`; còn lại → `Event.HitReact.Light` (spec §1). Stamina **được phép âm nhẹ** theo spec §3.
- Ability base: `ActivationPolicy` (OnInputTriggered / WhileInputActive / OnSpawn), `InputTag` (FGameplayTag), helper lấy `AEclipseCharacterBase` sẽ thêm ở T-012 (không include Characters từ Abilities — dùng `GetAvatarActorFromActorInfo()`).
- Không có magic number: giá trị khởi đầu (400/100/30) nằm ở GE init (`GE_Init_Player`, con người tạo theo hướng dẫn) hoặc DataTable, không trong constructor.

## Tiêu chí hoàn thành (kiểm tra được)
- [ ] Build PASS.
- [ ] Test `Eclipse.Abilities.AttributeSet`: apply damage meta → Health giảm đúng, clamp ≥ 0, gửi event đúng tag.
- [ ] `grep -rn '#include "Characters/' Unreal/Source/Eclipse/Abilities` → không có kết quả.
- [ ] Review chéo GPT 6.1 (tuỳ chọn) ghi vào mục Review.

---
## Handoff
