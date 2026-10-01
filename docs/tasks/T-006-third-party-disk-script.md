# T-006 — `docs/THIRD_PARTY.md` mẫu + script `Tools/check_disk.sh`

| | |
|---|---|
| Status | DONE |
| Milestone | M0 |
| Tier | B |
| Gợi ý model | Gemini Flash 3.8 hoặc GPT Luna 6 |
| Phụ thuộc | T-002 |
| Branch | `task/T-006-third-party-disk` (tạo từ `main`) |

## Mục tiêu
1. Một file ghi nguồn gốc/license mọi asset bên ngoài (GASP, pack Fab...).
2. Một script bash chạy trong **Git Bash trên Windows** in dung lượng các thư mục lớn và cảnh báo khi ổ C: sắp đầy.

## Đọc trước
- `AGENTS.md`, `docs/05_HARDWARE_AND_DISK.md` §2 (quy tắc "dưới 30 GB trống → dừng")

## Được phép sửa / tạo
- `docs/THIRD_PARTY.md` (tạo mới)
- `Tools/check_disk.sh` (tạo mới)
- Task card này (Handoff)

## Cấm
- Không sửa file nào khác (kể cả `.gitattributes`, `.gitignore`, `README.md`).
- Script **chỉ đọc**: không xoá, không di chuyển, không ghi file nào.

## Các bước
### 1. `docs/THIRD_PARTY.md`
Tiếng Việt. Nội dung đúng như sau (giữ nguyên tiêu đề cột), thêm sẵn **một dòng** cho GASP với các ô chưa biết ghi `CHƯA XÁC MINH (T-008)`:
```markdown
# THIRD PARTY — Asset & code bên ngoài

> Mọi asset/code không do dự án tự làm PHẢI có một dòng ở đây TRƯỚC khi migrate vào `Unreal/Content`.
> Không rõ license → không dùng.

| Tên | Nguồn (URL) | Tác giả | License | Dùng thương mại? | Ngày tải | Đường dẫn trong project | Dung lượng | Dùng cho | Ghi chú |
|---|---|---|---|---|---|---|---|---|---|
```
Dòng GASP: Tên `Game Animation Sample`, Tác giả `Epic Games`, Dùng cho `Locomotion Motion Matching (ADR-007)`.

### 2. `Tools/check_disk.sh`
Yêu cầu:
- Dòng đầu `#!/usr/bin/env bash`, sau đó `set -u` (không dùng `set -e` vì `du` có thể báo lỗi quyền trên vài file).
- Tự xác định thư mục gốc repo: `ROOT="$(cd "$(dirname "$0")/.." && pwd)"`. Chạy được từ bất kỳ thư mục nào.
- In bảng 2 cột (dung lượng, đường dẫn) cho từng mục dưới đây theo đúng thứ tự. Mục không tồn tại → in `-` và `(không có)`, **không** báo lỗi:
  1. `$ROOT/Unreal/Content`
  2. `$ROOT/Unreal/DerivedDataCache`
  3. `$ROOT/Unreal/Intermediate`
  4. `$ROOT/Unreal/Saved`
  5. `$ROOT/Unreal/Binaries`
  6. `$ROOT/.git` (tổng)
  7. `$ROOT/.git/lfs`
  8. Zen cache: `"$LOCALAPPDATA/UnrealEngine/Common/Zen/Data"` — ghi chú cạnh dòng `(đường dẫn CHƯA XÁC MINH, xem T-004)`. Nếu biến `LOCALAPPDATA` trống → coi như không tồn tại.
  9. Google Drive cache: `"$LOCALAPPDATA/Google/DriveFS"`.
- Lấy dung lượng bằng `du -sh "<path>" 2>/dev/null | cut -f1`.
- Cuối cùng in dung lượng trống ổ C: bằng `df -h /c | tail -1` và số GB trống dạng số nguyên bằng `df -BG /c | tail -1 | awk '{print $4}' | tr -d 'G'`.
- Nếu GB trống `< 30` → in dòng `CẢNH BÁO: ổ C: còn dưới 30 GB — dừng thêm asset, dọn dẹp (05_HARDWARE_AND_DISK.md §2)` và `exit 2`. Ngược lại `exit 0`.
- Comment trong script bằng tiếng Anh, ngắn.
- Line ending LF (`.gitattributes` đã ép `*.sh eol=lf`).

## Tiêu chí hoàn thành (kiểm tra được)
- [x] `bash Tools/check_disk.sh; echo "exit=$?"` chạy trong Git Bash từ root repo → in đủ 9 dòng + dòng dung lượng trống, `exit=0` (máy hiện còn > 100 GB).
- [x] Chạy từ thư mục khác: `cd /c && bash /c/Users/ADMIN/Downloads/GAME_TEST/Tools/check_disk.sh` → kết quả giống hệt.
- [x] `grep -nE 'rm |mv |> ' Tools/check_disk.sh` → **không có kết quả** (script chỉ đọc).
- [x] `docs/THIRD_PARTY.md` có đúng 10 cột và 1 dòng GASP.
- [x] `git diff --stat main` chỉ có 3 file: `docs/THIRD_PARTY.md`, `Tools/check_disk.sh`, task card này.
- Build C++: không áp dụng.

## Câu hỏi / Blocker
_Không có_

---
## Handoff (agent điền khi xong)
- File đã sửa/tạo:
  - `docs/THIRD_PARTY.md` (tạo mới)
  - `Tools/check_disk.sh` (tạo mới)
  - `docs/tasks/T-006-third-party-disk-script.md` (cập nhật)
- Output thật của `bash Tools/check_disk.sh` (dán nguyên văn):
```
0        /c/Users/ADMIN/Downloads/GAME_TEST/Unreal/Content
1.9M     /c/Users/ADMIN/Downloads/GAME_TEST/Unreal/DerivedDataCache
2.7G     /c/Users/ADMIN/Downloads/GAME_TEST/Unreal/Intermediate
3.9M     /c/Users/ADMIN/Downloads/GAME_TEST/Unreal/Saved
60M      /c/Users/ADMIN/Downloads/GAME_TEST/Unreal/Binaries
451K     /c/Users/ADMIN/Downloads/GAME_TEST/.git (tổng)
4.0K     /c/Users/ADMIN/Downloads/GAME_TEST/.git/lfs
1.3G     C:\Users\ADMIN\AppData\Local/UnrealEngine/Common/Zen/Data (đường dẫn CHƯA XÁC MINH, xem T-004)
42M      C:\Users\ADMIN\AppData\Local/Google/DriveFS
C:              450G  304G  146G  68% /c
```
- Chưa làm / CHƯA XÁC MINH:
  - Đường dẫn Zen Data (`%LOCALAPPDATA%\UnrealEngine\Common\Zen\Data`) hiện đo được 1.3G nhưng chờ T-004 xác minh chính thức từ engine config/code.
  - Các trường chi tiết của GASP (License, URL, size, v.v.) trong `docs/THIRD_PARTY.md` chờ T-008 xác minh và điền bổ sung.

## Review (Tier A điền)
- Kết luận: **PASS** (Claude, 2026-10-01). Chạy lại script từ root repo và từ `/c`: đủ 9 dòng + dòng ổ đĩa, `exit=0`; grep `rm |mv |> ` không ra gì; bảng 10 cột, 1 dòng GASP; `git diff --stat main...` đúng 3 file. Script khớp spec, handoff trung thực (không bịa số).
- Lead tự chỉnh khi merge: bỏ ghi chú "CHƯA XÁC MINH" của đường dẫn Zen (đã xác minh ở T-004); điền dòng GASP bằng số đã biết (ngày tải, dung lượng); URL + license vẫn chờ chủ dự án chép từ trang Fab.
