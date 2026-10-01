# T-012 — Header Character/Controller/GameMode + `.cpp` khung (để T-013 điền)

| | |
|---|---|
| Status | TODO |
| Milestone | M1 |
| Tier | A |
| Gợi ý model | Opus 5.5 |
| Phụ thuộc | T-011 |
| Branch | `task/T-012-character-headers` |

## Mục tiêu
Các class gameplay chính có header hoàn chỉnh (UPROPERTY, UFUNCTION, comment mô tả hành vi từng hàm đủ để Tier B viết thân hàm) và `.cpp` khung **build PASS** (thân hàm rỗng/`// T-013:` placeholder, không có hàm khai báo mà thiếu định nghĩa).

## Đọc trước
- `docs/01_ARCHITECTURE.md` §4, §5; `docs/04_COMBAT_GAS_SPEC.md` §3; T-014 (danh sách `IA_*`)

## Được phép sửa / tạo
- `Unreal/Source/Eclipse/Characters/EclipseCharacterBase.h/.cpp`
- `Unreal/Source/Eclipse/Characters/EclipsePlayerCharacter.h/.cpp`
- `Unreal/Source/Eclipse/Characters/EclipsePlayerController.h/.cpp`
- `Unreal/Source/Eclipse/Core/EclipseGameMode.h/.cpp`, `Core/EclipseGameInstance.h/.cpp`
- `Unreal/Source/Eclipse/Characters/EclipseInputConfig.h/.cpp` (Data Asset map `UInputAction*` ↔ `FGameplayTag`)
- `docs/tasks/T-013-character-cpp.md` (Claude viết card chi tiết cho Tier B sau khi header chốt)
- Xoá `Characters/.gitkeep`

## Phạm vi
- CharacterBase: ASC + CombatAttributeSet (subobject), `IAbilitySystemInterface`, `IEclipseDamageable`, `IEclipseTargetable`; danh sách `StartupAbilities`/`StartupEffects` (EditDefaultsOnly) cấp khi `PossessedBy`/`BeginPlay`.
- PlayerCharacter: SpringArm + Camera (giá trị UPROPERTY, tuning ở T-019), chỗ gắn `UEclipseLockOnComponent` để **trống** tới T-017.
- PlayerController: thêm `IMC_Gameplay`, bind `IA_Move`/`IA_Look` trực tiếp, các IA còn lại → `ASC->AbilityInputTagPressed/Released` qua `UEclipseInputConfig`.
- Không làm: input buffer (M2), lock-on (T-017), camera tuning (T-019).

## Tiêu chí hoàn thành (kiểm tra được)
- [ ] Build PASS.
- [ ] Mọi hàm có placeholder đều có comment `// T-013:` mô tả hành vi mong đợi; `grep -rn "T-013:" Unreal/Source` ra danh sách công việc của T-013.
- [ ] Checklist review `02_TEAM_WORKFLOW.md` §5 tự kiểm.
- [ ] Card `T-013-character-cpp.md` đã viết, liệt kê chính xác từng hàm cần điền.

---
## Handoff
