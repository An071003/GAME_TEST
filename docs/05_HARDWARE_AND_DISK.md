# 05 — HARDWARE & DISK BUDGET

## 1. Máy dev (quét ngày 2026-09-30)
| Thành phần | Giá trị | Ảnh hưởng |
|---|---|---|
| CPU | i7-13620H 10C/16T | Build C++ ổn; shader compile lần đầu lâu (~30–90 phút) |
| GPU | RTX 4050 Laptop **6 GB VRAM** | Giới hạn chính cho Lumen/Nanite/texture trong Editor |
| RAM | 32 GB | Đủ |
| Ổ | 1× NVMe 512 GB (C: hiển thị 450 GB), **còn ~148 GB** (đo 2026-09-30, sau khi tạo project `Unreal/` 4.5 GB) | Giới hạn chính cho scope. Ngân sách §2 vẫn tính theo mức 113 GB để giữ biên an toàn |
| Google Drive | `G:` (Drive for desktop, Stream), gói 5 TB | Ổ `G:` báo 450 GB / còn ~140 GB vì dùng chung dung lượng C: cho cache; dung lượng thật nằm trên cloud |
| UE | 5.8 (launcher) tại `C:\Program Files\Epic Games\UE_5.8` | |
| Blender | 4.5 | Kế hoạch gốc ghi 5.x — dùng 4.5 cho tới khi có lý do nâng |
| VS | Community 2026 (18.10.3), workload "Game development with C++" đã cài. MSVC **14.51.36231** (không nằm trong Preferred của UE 5.8 nhưng không bị Banned, ≥ Minimum 14.38.33130). Windows SDK 10.0.26100.0 | Chờ T-003 build xác nhận. Nếu lỗi toolchain: cài `Microsoft.VisualStudio.Component.VC.14.50.18.0.x86.x64` (Preferred 14.50.35717+) song song |

## 2. Ngân sách ổ đĩa (≈113 GB trống)
| Mục | Trần | Ghi chú |
|---|---|---|
| Dự trữ cho Windows/update | 20 GB | Không bao giờ dùng |
| DDC / Zen local cache | 25 GB | Đặt giới hạn (T-004). Xoá được, sẽ build lại |
| `Unreal/Content` | 25 GB đến Vertical Slice | GASP + vài pack Fab đã có thể 5–10 GB — chọn lọc |
| `.git` + LFS objects | ≈ bằng Content | LFS lưu **thêm một bản** mỗi binary |
| Intermediate / Binaries / Saved | 10 GB | Không commit |
| Build đóng gói | 0 GB trên C: dài hạn | Đóng gói xong → nén, upload Drive, xoá trên C: (không đóng gói thẳng vào thư mục Drive: nhiều file nhỏ, chậm) |
| ArtSource (.blend, .psd) | ngoài repo | Xem §3 |

**Tổng thực tế ~100 GB → sát trần.** Giải pháp: dùng **Google Drive for desktop (5 TB, chế độ Stream)** cho lưu trữ nguội — ArtSource, backup, archive build đóng gói. Không cần mua SSD ngoài cho mục đích lưu trữ; ổ ngoài chỉ đáng mua nếu cần thêm chỗ cho dữ liệu đang làm việc (USB chậm hơn NVMe nội).

Quy tắc:
- **KHÔNG đặt `Unreal/`, `.git` hoặc DDC trong thư mục Google Drive** (client đồng bộ khoá/sửa file giữa chừng → hỏng repo và cache).
- Dùng **Stream**, không dùng Mirror: Mirror chép toàn bộ về C: và ăn đúng phần dung lượng đang thiếu. File đang làm việc → "Available offline"; backup/archive → online-only.
- Cache của Stream nằm ở `%LOCALAPPDATA%\Google\DriveFS` trên C:; theo dõi và dọn khi cần (kiểm tra Preferences xem có giới hạn/đổi vị trí cache không — CHƯA XÁC MINH).
- Không mở trực tiếp `.blend` nặng từ file online-only; đánh dấu offline hoặc chép về máy trước.
- Không import pack Fab "cho có". Tạo project tạm để xem pack, chỉ migrate asset cần dùng.
- Kiểm tra dung lượng mỗi tuần: `du -sh Unreal/Content Unreal/DerivedDataCache .git`.
- Dưới 30 GB trống → dừng thêm asset, dọn dẹp.

## 3. ArtSource
- Đặt trong thư mục Google Drive (Stream, xem §2), **không** trong git repo.
- Vị trí: `G:\My Drive\Eclipse\ArtSource` (nguồn art), `G:\My Drive\Eclipse\Backups` (zip project, `git bundle`), `G:\My Drive\Eclipse\Builds` (archive build đã nén).
- Cấu trúc giữ như kế hoạch gốc: `ArtSource/Blender/{Characters,Enemies,Bosses,Weapons,Architecture,Props}`.
- Chỉ file export (FBX) đi vào Unreal; file FBX có thể xoá sau khi import thành công (luôn export lại được từ .blend).

## 4. Remote / backup
- GitHub có hạn mức Git LFS (kiểm tra hạn mức hiện tại trước khi dùng); dự án này sẽ vượt nhanh.
- Remote (chủ dự án chốt 2026-09-30): GitHub `https://github.com/An071003/GAME_TEST.git` (remote `origin`). Hạn mức LFS của GitHub nhỏ → theo dõi dung lượng LFS; nếu vượt thì chuyển sang Azure DevOps / dịch vụ có LFS lớn. **Không** dùng thư mục Google Drive làm bare repo remote.
- Backup định kỳ lên Drive: `git bundle create ... --all` + zip project (loại `Intermediate`, `DerivedDataCache`, `Saved`, `Binaries`).

## 5. GPU / rendering (6 GB VRAM)
- Editor: Engine Scalability = **High** (không Epic). Tắt "Realtime" viewport khi không cần.
- Lumen: dùng mặc định (software/hardware tùy project setting) — đo thực tế ở M1, ghi kết quả vào đây.
- Nanite: dùng cho static mesh môi trường. Không cho skeletal mesh nhân vật trừ khi đã đo.
- Virtual Shadow Maps: bật, theo dõi VRAM.
- Texture: hero/boss 4K, vũ khí 2K, môi trường 2K tiling, prop 1K, clutter 512. **Không 8K.**
- Texture streaming pool: theo dõi cảnh báo "Texture streaming pool over budget".

## 6. Performance target
- 60 FPS @ 1080p, preset High, **trên chính máy này** (TSR upscale được phép).
- Budget: Game thread ≤ 6 ms, GPU ≤ 14 ms (để dư).
- Đo bằng `stat unit`, `stat gpu`, Unreal Insights. Boss arena đo khi: boss + 3 enemy + VFX + UI cùng lúc.
