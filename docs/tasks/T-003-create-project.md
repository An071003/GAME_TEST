# T-003 — Tạo project C++ `Eclipse`

| | |
|---|---|
| Status | TODO |
| Milestone | M0 |
| Tier | A (Claude) + Human |
| Phụ thuộc | T-001, T-002 |
| Branch | `task/T-003-create-project` |

## Mục tiêu
`Unreal/Eclipse.uproject` với module C++ `Eclipse`, build PASS, mở được Editor, plugin M0 đã bật.

## Đọc trước
- `docs/01_ARCHITECTURE.md` §2, §10; `docs/DECISIONS.md` ADR-001, ADR-005

## Các bước
1. **Human:** Unreal Project Browser → Games → **Blank**, **C++**, Desktop, Scalable = **Maximum**, Starter Content = **OFF**, Raytracing = OFF. Vị trí: `C:/Users/ADMIN/Downloads/GAME_TEST/`, tên: `Unreal` → sau đó đổi tên project nếu cần sao cho kết quả là `GAME_TEST/Unreal/Eclipse.uproject` (Claude sẽ hướng dẫn chi tiết nếu launcher không cho đặt khác tên thư mục).
2. **Claude:** chuẩn hoá `Source/` theo `01_ARCHITECTURE.md` §2 (tạo thư mục con, log category `LogEclipse`), `Eclipse.Build.cs` thêm dependency: `GameplayAbilities`, `GameplayTags`, `GameplayTasks`, `EnhancedInput`, `AIModule`, `StateTreeModule`, `GameplayStateTreeModule`, `MotionWarping`, `UMG`, `Niagara`.
3. **Claude:** bật plugin trong `.uproject` theo §10; xác minh tên plugin/module tồn tại trong `C:/Program Files/Epic Games/UE_5.8/Engine/Plugins` (không đoán).
4. Build theo `AGENTS.md` §4.
5. **Human:** mở Editor, chờ compile shader, xác nhận không lỗi plugin.

## Tiêu chí hoàn thành
- [ ] Build PASS.
- [ ] Editor mở được, Output Log không có lỗi plugin.
- [ ] Dung lượng `Unreal/` sau lần mở đầu được ghi vào handoff.

---
## Handoff
