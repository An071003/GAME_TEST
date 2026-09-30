# T-003 — Tạo project C++ `Eclipse`

| | |
|---|---|
| Status | REVIEW |
| Milestone | M0 |
| Tier | A (Claude) + Human |
| Phụ thuộc | T-001, T-002 |
| Branch | `task/T-003-create-project` |

## Mục tiêu
`Unreal/Eclipse.uproject` với module C++ `Eclipse`, build PASS, mở được Editor, plugin M0 đã bật.

## Đọc trước
- `docs/01_ARCHITECTURE.md` §2, §10; `docs/DECISIONS.md` ADR-001, ADR-005

## Được phép sửa / tạo
- `Unreal/Eclipse.uproject` (bật đúng 9 plugin ở bước 3; không bật StructUtils)
- `Unreal/Source/Eclipse/Eclipse.Build.cs`, `Eclipse.h`, `Eclipse.cpp`
- `Unreal/Source/Eclipse/{Core,Abilities,Combat,Characters,AI,Inventory,World,Save,UI}/.gitkeep`
- `Unreal/Config/DefaultEngine.ini` (chỉ `r.RayTracing*` → False)
- `.gitignore` (thêm pattern file sinh ra của Unreal)
- Task card này

## Các bước
1. **Human:** Unreal Project Browser → Games → **Blank**, **C++**, Desktop, Scalable = **Maximum**, Starter Content = **OFF**, Raytracing = OFF. Vị trí: `C:/Users/ADMIN/Downloads/GAME_TEST/`, tên: `Unreal` → sau đó đổi tên project nếu cần sao cho kết quả là `GAME_TEST/Unreal/Eclipse.uproject` (Claude sẽ hướng dẫn chi tiết nếu launcher không cho đặt khác tên thư mục).
2. **Claude:** chuẩn hoá `Source/` theo `01_ARCHITECTURE.md` §2 (tạo thư mục con, log category `LogEclipse`), `Eclipse.Build.cs` thêm dependency: `GameplayAbilities`, `GameplayTags`, `GameplayTasks`, `EnhancedInput`, `AIModule`, `StateTreeModule`, `GameplayStateTreeModule`, `MotionWarping`, `UMG`, `Niagara`.
3. **Claude:** bật plugin trong `.uproject` theo §10; xác minh tên plugin/module tồn tại trong `C:/Program Files/Epic Games/UE_5.8/Engine/Plugins` (không đoán).
4. Build theo `AGENTS.md` §4.
5. **Human:** mở Editor, chờ compile shader, xác nhận không lỗi plugin.

## Tiêu chí hoàn thành
- [x] Build PASS.
- [x] Editor mở được, Output Log không có lỗi plugin.
- [x] Dung lượng `Unreal/` sau lần mở đầu được ghi vào handoff.

---
## Handoff
- Bước 1 (Human): project tạo ở `Unreal/Eclipse/`, đã đưa lên `Unreal/Eclipse.uproject` cho khớp tài liệu.
- Tạo/sửa: `Unreal/Eclipse.uproject` (bật GameplayAbilities, EnhancedInput, PoseSearch, MotionWarping, Chooser, AnimationWarping, StateTree, GameplayStateTree, Niagara), `Source/Eclipse/Eclipse.Build.cs` (đủ dependency theo bước 2, thêm Slate/SlateCore private, include path module root), `Eclipse.h/.cpp` (`LogEclipse`), 9 thư mục con có `.gitkeep`, `Config/DefaultEngine.ini` (RayTracing → False, đúng yêu cầu bước 1), `.gitignore` (+`Unreal/*.slnx`).
- Đã xác minh trong `UE_5.8/Engine/Plugins`: mọi `.uplugin` trên đều tồn tại; module `StateTreeModule`, `GameplayStateTreeModule`, `MotionWarping`, `GameplayAbilities`, `GameplayTags`, `GameplayTasks`, `AIModule` tồn tại.
- **StructUtils: KHÔNG bật.** `FInstancedStruct` (`StructUtils/InstancedStruct.h`) đã nằm trong CoreUObject ở 5.8; plugin StructUtils chỉ còn là Experimental.
- Build `EclipseEditor Win64 Development`: **PASS** (61 s). Chỉ có warning C4996 nằm trong header engine.
- Dung lượng `Unreal/` hiện tại: 4.5 GB (chưa mở lại Editor sau thay đổi plugin).
- CHƯA làm: `Substrate=True` và `GameDefaultMap=OpenWorld` trong DefaultEngine.ini là mặc định template, chưa đổi (ngoài phạm vi task; đề xuất xem lại ở M0/M1).
- **Human cần làm (bước 5):** đóng Visual Studio; mở `Unreal/Eclipse.uproject`, chờ compile shader (lần đầu sau khi đổi plugin có thể vài phút); mở Window → Developer Tools → Output Log, lọc "Error" và "Warning" mục plugin; xác nhận không có lỗi plugin; báo lại kết quả và dung lượng `du -sh Unreal`.
- **Bước 5 xác nhận (2026-09-30):** Editor mở được; `Saved/Logs/Eclipse.log` có 0 dòng `Error:`, đủ 9 plugin M0 được mount. Chỉ có cảnh báo vô hại `PixWinPlugin` (không chạy từ PIX). Dung lượng `Unreal/` sau lần mở: **4.5 GB**.
