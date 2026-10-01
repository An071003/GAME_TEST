# T-013 — Điền thân hàm `.cpp` cho Character/Controller/InputConfig

| | |
|---|---|
| Status | TODO |
| Milestone | M1 |
| Tier | B |
| Gợi ý model | GPT Luna 6 |
| Phụ thuộc | T-012 (merge vào `main`) |
| Không chạy song song với | T-016, T-017 (cùng thư mục `Characters/`) |
| Branch | `task/T-013-character-cpp` |

## Mục tiêu
Mọi hàm đang có comment `// T-013:` có thân hàm đúng như comment mô tả. Build PASS, không còn `// T-013:` nào.

## Đọc trước
- `AGENTS.md`
- Header tương ứng (comment trong header là hợp đồng): `Characters/EclipseCharacterBase.h`, `EclipsePlayerController.h`, `EclipseInputConfig.h`
- `Abilities/EclipseAbilitySystemComponent.h`, `Core/EclipseGameplayTags.h`

## Được phép sửa
CHỈ 3 file, và chỉ trong thân hàm có `// T-013:`:
- `Unreal/Source/Eclipse/Characters/EclipseCharacterBase.cpp`
- `Unreal/Source/Eclipse/Characters/EclipsePlayerController.cpp`
- `Unreal/Source/Eclipse/Characters/EclipseInputConfig.cpp`

KHÔNG sửa: bất kỳ `.h`, `Eclipse.Build.cs`, file ngoài danh sách. Nếu cần thêm hàm/biến/include header mới → dừng, ghi vào Handoff, Lead sẽ sửa.

## Danh sách hàm cần điền (đủ 11)
| # | Hàm | Việc cần làm (chi tiết trong comment tại chỗ) |
|---|---|---|
| 1 | `AEclipseCharacterBase::CanBeDamaged` | `false` nếu `IsDead()` hoặc ASC có `State.Invulnerable`, ngược lại `true` |
| 2 | `AEclipseCharacterBase::IsTargetable` | `!IsDead()` |
| 3 | `AEclipseCharacterBase::GetTargetLocation` | vị trí socket/bone `spine_03` nếu mesh có, không thì `GetActorLocation()` |
| 4 | `AEclipseCharacterBase::IsDead` | ASC hợp lệ và có tag `EclipseTags::State_Dead.GetTag()` |
| 5 | `AEclipseCharacterBase::InitializeAbilities` | guard `bAbilitiesInitialized`; `InitAbilityActorInfo(this, this)`; `GiveAbility(FGameplayAbilitySpec(Class, 1))` cho từng `StartupAbilities`; áp từng `StartupEffects` lên chính mình |
| 6 | `AEclipsePlayerController::BeginPlay` | thêm `GameplayMappingContext` vào `UEnhancedInputLocalPlayerSubsystem` |
| 7 | `AEclipsePlayerController::SetupInputComponent` | bind Move/Look + từng `AbilityInputs` (Started → Pressed, Completed → Released) |
| 8 | `AEclipsePlayerController::Move` | `AddMovementInput` theo yaw của control rotation |
| 9 | `AEclipsePlayerController::Look` | `AddYawInput` / `AddPitchInput` |
| 10 | `AEclipsePlayerController::AbilityInputPressed/Released` + `GetPawnASC` | chuyển tag sang `UEclipseAbilitySystemComponent` của pawn |
| 11 | `UEclipseInputConfig::FindInputTagForAction` | tìm trong `AbilityInputs` |

Gợi ý code cho các chỗ hay sai:
```cpp
// Move (item 8)
const FVector2D Axis = Value.Get<FVector2D>();
const FRotator Yaw(0.f, GetControlRotation().Yaw, 0.f);
const FVector Forward = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
const FVector Right = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);

// BindAction với tham số thêm (item 7)
EIC->BindAction(Entry.Action, ETriggerEvent::Started, this, &ThisClass::AbilityInputPressed, Entry.InputTag);

// InitializeAbilities (item 5)
AbilitySystemComponent->InitAbilityActorInfo(this, this);
AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityClass, 1));
FGameplayEffectContextHandle Ctx = AbilitySystemComponent->MakeEffectContext();
Ctx.AddSourceObject(this);
AbilitySystemComponent->ApplyGameplayEffectToSelf(EffectClass->GetDefaultObject<UGameplayEffect>(), 1.f, Ctx);
```
Log dùng `UE_LOG(LogEclipse, Warning, ...)` (khai báo trong `Eclipse.h`; thêm `#include "Eclipse.h"` vào `.cpp` nếu cần).

## Tiêu chí hoàn thành (kiểm tra được)
- [ ] Build PASS: lệnh ở `AGENTS.md` §4.
- [ ] `grep -rn "T-013:" Unreal/Source` → không có kết quả.
- [ ] `git diff --stat main...HEAD` chỉ liệt kê 3 file được phép (+ card này).
- [ ] `grep -rn '#include "\(UI\|AI\)/' Unreal/Source/Eclipse/Characters` → không có kết quả.
- [ ] Không còn `return false;` / `return FVector::ZeroVector;` / `return nullptr;` placeholder ở các hàm trên (trừ trường hợp logic thật trả về giá trị đó).
- [ ] Test hiện có vẫn PASS: `Automation RunTests Eclipse` (headless, lệnh ở card T-010).

---
## Handoff
(Tier B điền: file đã sửa, kết quả build/grep, điều không chắc chắn.)

## Review
(Lead điền.)
