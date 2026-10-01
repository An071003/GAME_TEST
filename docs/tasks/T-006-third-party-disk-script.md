# T-006 — `docs/THIRD_PARTY.md` mẫu + script `Tools/check_disk.sh`

| | |
|---|---|
| Status | TODO |
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
- [ ] `bash Tools/check_disk.sh; echo "exit=$?"` chạy trong Git Bash từ root repo → in đủ 9 dòng + dòng dung lượng trống, `exit=0` (máy hiện còn > 100 GB).
- [ ] Chạy từ thư mục khác: `cd /c && bash /c/Users/ADMIN/Downloads/GAME_TEST/Tools/check_disk.sh` → kết quả giống hệt.
- [ ] `grep -nE 'rm |mv |> ' Tools/check_disk.sh` → **không có kết quả** (script chỉ đọc).
- [ ] `docs/THIRD_PARTY.md` có đúng 10 cột và 1 dòng GASP.
- [ ] `git diff --stat main` chỉ có 3 file: `docs/THIRD_PARTY.md`, `Tools/check_disk.sh`, task card này.
- Build C++: không áp dụng.

## Câu hỏi / Blocker
_(ghi vào đây nếu dừng)_

---
## Handoff (agent điền khi xong)
- File đã sửa/tạo:
- Output thật của `bash Tools/check_disk.sh` (dán nguyên văn):
- Chưa làm / CHƯA XÁC MINH:

## Review (Tier A điền)
- Kết luận:
- Yêu cầu sửa:
