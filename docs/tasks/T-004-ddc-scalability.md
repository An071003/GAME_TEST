# T-004 — Giới hạn DDC/Zen cache + Editor scalability cho máy 6 GB VRAM

| | |
|---|---|
| Status | TODO |
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
- Đường dẫn thật trên máy của `%ENGINEVERSIONAGNOSTICINSTALLEDUSERDIR%`: **CHƯA XÁC MINH** (dự kiến `%LOCALAPPDATA%\UnrealEngine\Common\`).

## Được phép sửa / tạo
- `Unreal/Config/DefaultEngine.ini` (chỉ mục `[Zen.AutoLaunch]` — Claude)
- `docs/05_HARDWARE_AND_DISK.md` §1, §2, §5 (ghi số liệu)
- Task card này

## Các bước
1. **Claude:** xác minh đường dẫn Zen Data thật trên máy + dung lượng hiện tại.
2. **Claude:** xác minh cú pháp override `ExtraArgs` ở cấp project (đọc source `ZenServerInterface.cpp` của 5.8, không đoán) rồi override: thời hạn GC 7 ngày, ngưỡng low-disk ≈ 30 GB (khớp quy tắc "dưới 30 GB dừng" ở doc 05). Không đổi DataPath sang `G:`.
3. **Claude:** viết hướng dẫn Editor từng bước vào mục "Hướng dẫn Human" dưới đây.
4. **Human:** Editor → Settings → Engine Scalability = **High**; các tuỳ chọn Editor Preferences → Performance và kiểm tra Zen theo "Hướng dẫn Human".
5. **Claude:** đánh giá `Substrate=True` (mặc định template, treo từ T-003) với 6 GB VRAM → chỉ ghi khuyến nghị vào doc 05 §5; đổi ini (nếu cần) là task riêng, chủ dự án duyệt.
6. Build theo `AGENTS.md` §4, mở Editor, kiểm tra Output Log không có lỗi Zen.

## Tiêu chí hoàn thành (kiểm tra được)
- [ ] `DefaultEngine.ini` có override `[Zen.AutoLaunch]`, Editor khởi động không lỗi Zen.
- [ ] `05_HARDWARE_AND_DISK.md` ghi đường dẫn Zen Data thật + dung lượng đo được.
- [ ] Scalability High đã đặt (con người xác nhận).

## Hướng dẫn Human
_(Claude điền ở bước 3)_

## Câu hỏi / Blocker

---
## Handoff
