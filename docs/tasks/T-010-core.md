# T-010 — `Core/`: native gameplay tags, interfaces, event subsystem

| | |
|---|---|
| Status | DONE |
| Milestone | M1 |
| Tier | A |
| Gợi ý model | Opus 5.5 |
| Phụ thuộc | T-003 (merge vào `main`) |
| Branch | `task/T-010-core` |

## Mục tiêu
Tầng `Core/` tồn tại và build PASS: mọi tag C++ cần ở M1–M2 được khai báo native, 4 interface, kiểu dữ liệu dùng chung, `UEclipseEventSubsystem`.

## Đọc trước
- `docs/01_ARCHITECTURE.md` §2, §3, §6, §7; `docs/04_COMBAT_GAS_SPEC.md` §2
- `docs/DECISIONS.md` ADR-010, ADR-011

## Được phép sửa / tạo
- `Unreal/Source/Eclipse/Core/EclipseGameplayTags.h/.cpp`
- `Unreal/Source/Eclipse/Core/EclipseTypes.h` (`FEclipseDamageContext`, enum dùng chung)
- `Unreal/Source/Eclipse/Core/EclipseDamageable.h`, `EclipseTargetable.h`, `EclipseInteractable.h`, `EclipseSaveable.h` (+ `.cpp` nếu UHT cần)
- `Unreal/Source/Eclipse/Core/EclipseEventSubsystem.h/.cpp`
- `Unreal/Source/Eclipse/Tests/EclipseEventSubsystemTest.cpp` (automation test, `WITH_DEV_AUTOMATION_TESTS`)
- Xoá `Core/.gitkeep`

## Thiết kế
- Tags: macro `UE_DECLARE_GAMEPLAY_TAG_EXTERN` / `UE_DEFINE_GAMEPLAY_TAG_COMMENT` trong namespace `EclipseTags` — đủ danh sách spec §2 **trừ** `Status.*` (sau M4). Xác minh macro trong header engine 5.8 trước khi dùng.
- `IEclipseSaveable`: chỉ khai báo `GetSaveId()`; `WriteSave/ReadSave` thêm ở M4 khi có `FEclipseActorSaveData` (tránh định nghĩa kiểu save sớm).
- Event subsystem: `Broadcast(FGameplayTag, const FInstancedStruct&)`, `Listen(FGameplayTag, FEclipseEventDelegate) -> FEclipseEventHandle`, `Unlisten(Handle)`. Native delegate (C++) + một bản BlueprintAssignable để UI BP dùng. Listener khớp tag chính xác (không match cha) — đủ cho M1–M4.

## Tiêu chí hoàn thành (kiểm tra được)
- [x] Build PASS (`AGENTS.md` §4).
- [x] `grep -rn "RequestGameplayTag" Unreal/Source` → không có kết quả ngoài `Core/`.
- [x] `grep -rnE '#include "(Abilities|Combat|Characters|AI|Inventory|World|Save|UI)/' Unreal/Source/Eclipse/Core` → không có kết quả.
- [x] Automation test `Eclipse.Core.EventSubsystem` PASS (Broadcast → listener nhận payload; Unlisten → không nhận nữa). Chạy bằng commandlet `-ExecCmds="Automation RunTests Eclipse.Core"`; nếu chưa chạy được headless → con người chạy trong Session Frontend và ghi kết quả.
- [ ] Editor mở: Project Settings → GameplayTags hiển thị các tag native (con người xác nhận).

---
## Handoff
- Files: `Core/EclipseGameplayTags.h/.cpp` (48 tag native, đủ spec §2 trừ `Status.*`), `EclipseTypes.h`, 4 interface (header-only, `MinimalAPI`), `EclipseEventSubsystem.h/.cpp`, `Tests/EclipseEventSubsystemTest.cpp`; xoá `Core/.gitkeep`.
- Build `EclipseEditor Win64 Development`: PASS.
- Test: `UnrealEditor-Cmd.exe Eclipse.uproject -ExecCmds="Automation RunTests Eclipse.Core; Quit" -unattended -nopause -nosplash -NullRHI` → `Result={Success}` cho `Eclipse.Core.EventSubsystem` (chạy headless được).
- Phát hiện: `UGameInstanceSubsystem` có `ClassWithin=GameInstance` nên test phải tạo `UGameInstance` làm outer.
- `FInstancedStruct` nằm trong CoreUObject 5.8 (`StructUtils/InstancedStruct.h`) → không cần thêm module vào `Build.cs`.
- **Human còn lại**: mở Editor → Project Settings → Project → GameplayTags → thấy các tag `State.*`, `Ability.*`... (nguồn Native). Nhắn "T-010: tag OK".
- **Human xác nhận (2026-10-01)**: Gameplay Tag Manager hiện đủ `State.Attacking`, `Ability.Attack.Light` (nguồn Native). T-010: tag OK.
