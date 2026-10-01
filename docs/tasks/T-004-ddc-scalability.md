# T-004 — Giới hạn DDC/Zen cache + Editor scalability cho máy 6 GB VRAM

| | |
|---|---|
| Status | IN_PROGRESS |
| Milestone | M0 |
| Tier | A (Claude viết hướng dẫn + sửa ini) → Human (thao tác Editor, xác nhận) |
| Gợi ý model | Opus 5.5 + Bạn |
| Phụ thuộc | T-003 |
| Branch | `task/T-004-ddc-scalability` |

## Mục tiêu
Cache dẫn xuất (Zen/DDC) không âm thầm ăn hết ổ C:, Editor chạy mượt ở Scalability High; số liệu được ghi vào `05_HARDWARE_AND_DISK.md`.

## Đọc trước
- `docs/05_HARDWARE_AND_DISK.md` §2, §5
- `UE_5.8/Engine/Config/BaseEngine.ini` mục `[Zen.AutoLaunch]`, `[InstalledDerivedDataBackendGraph]`

## Hiện trạng đã xác minh (2026-10-01, Claude)
- UE 5.8 dùng **Zen** làm local DDC. `[Zen.AutoLaunch] DataPath=%ENGINEVERSIONAGNOSTICINSTALLEDUSERDIR%Zen/Data` (dùng chung cho mọi project/phiên bản engine).
- GC mặc định trong `ExtraArgs`: `--gc-cache-duration-seconds 1209600` (14 ngày), `--gc-low-diskspace-threshold 2147483648` (2 GB — quá thấp với ổ 512 GB).
- Đường dẫn Zen Data thật (**đã xác minh**, có `auth cache cas gc logs`): `%LOCALAPPDATA%/UnrealEngine/Common/Zen/Data` — 1.3 GB sau khi mở Eclipse + GASP58. Zen dùng chung mọi project nên chỉ tính **một** lần trong ngân sách 25 GB.
- `zenserver.exe --help` (5.8) có cờ `--gc-disksize-softlimit <bytes>` (trần dung lượng, mặc định 0 = tắt), `--gc-low-diskspace-threshold <bytes>` (ngừng ghi khi ổ còn ít hơn), `--gc-cache-duration-seconds`. `ZenServerInterface.cpp` đọc `[Zen.AutoLaunch] ExtraArgs` bằng `GetString(..., GEngineIni)` → project ghi đè được nhưng **thay cả chuỗi**, nên phải lặp lại các cờ mặc định.
- Zen là instance **dùng chung**: override chỉ có hiệu lực khi Zen khởi động lại từ một Editor đọc `DefaultEngine.ini` này. Kiểm chứng bằng dòng `Command line:` trong `Zen/Data/logs/zenserver.log`.
- **Đã làm (Claude):** thêm `[Zen.AutoLaunch] ExtraArgs=...` vào `DefaultEngine.ini`: GC 7 ngày, trần mềm **25 GB** (`26843545600`), ngừng ghi khi ổ C: còn < **30 GB** (`32212254720`).

## Được phép sửa / tạo
- `Unreal/Config/DefaultEngine.ini` (chỉ mục `[Zen.AutoLaunch]` — Claude)
- `docs/05_HARDWARE_AND_DISK.md` §1, §2, §5 (ghi số liệu)
- Task card này

## Các bước
1. **Claude:** xác minh đường dẫn Zen Data thật trên máy + dung lượng hiện tại.
2. **Claude:** xác minh cú pháp override `ExtraArgs` ở cấp project (đọc source `ZenServerInterface.cpp` của 5.8, không đoán) rồi override: thời hạn GC 7 ngày, ngưỡng low-disk ≈ 30 GB (khớp quy tắc "dưới 30 GB dừng" ở doc 05). Không đổi DataPath sang `G:`.
3. **Claude:** viết hướng dẫn Editor từng bước vào mục "Hướng dẫn Human" dưới đây.
4. **Human:** làm theo "Hướng dẫn Human" (đóng Editor, tắt `zenserver.exe`, mở Eclipse, đặt Scalability High).
5. **Claude:** đánh giá `Substrate=True` (mặc định template, treo từ T-003) với 6 GB VRAM → chỉ ghi khuyến nghị vào doc 05 §5; đổi ini (nếu cần) là task riêng, chủ dự án duyệt.
6. **Claude:** không có thay đổi C++ nên không cần build; kiểm tra `Zen/Data/logs/zenserver.log` + Output Log không lỗi Zen.

## Tiêu chí hoàn thành (kiểm tra được)
- [ ] `DefaultEngine.ini` có override `[Zen.AutoLaunch]`; `zenserver.log` có dòng `Command line:` chứa `--gc-disksize-softlimit 26843545600`.
- [ ] `05_HARDWARE_AND_DISK.md` ghi đường dẫn Zen Data thật + dung lượng đo được.
- [ ] Scalability High đã đặt (con người xác nhận).

## Hướng dẫn Human

### Việc của bạn (≈10 phút, không cần build C++)
1. **Đóng mọi Unreal Editor** (kể cả GASP58) và Visual Studio nếu đang mở Eclipse.
2. Mở Task Manager (Ctrl+Shift+Esc) → tab Details → tìm `zenserver.exe`. Nếu còn → chuột phải → **End task** (nó tự thoát khi Editor đóng, nhưng nếu còn thì phải tắt để nhận cấu hình mới).
3. Mở `C:\Users\ADMIN\Downloads\GAME_TEST\Unreal\Eclipse.uproject` (lần này **không** mở GASP58 trước).
4. Khi Editor lên: nút **Settings** (góc phải viewport hoặc thanh trên cùng) → **Engine Scalability Settings** → chọn **High**. (Không chọn Epic/Cinematic.)
5. Đóng Editor, nhắn Claude: **"T-004: xong"**. Claude đọc `zenserver.log` để xác nhận cờ `--gc-disksize-softlimit 26843545600` đã được áp dụng, rồi ghi số liệu vào doc 05.

Nếu Editor báo lỗi/ cảnh báo về Zen khi mở: chụp dòng đó gửi Claude, **không** tự sửa `DefaultEngine.ini`.
Lưu ý: Scalability của Editor là thiết lập người dùng (lưu ngoài repo, `EditorSettings`), không commit được — chỉ cần bạn đặt một lần.

## Câu hỏi / Blocker

---
## Handoff
