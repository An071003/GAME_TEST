# T-001 — Toolchain C++ cho UE 5.8

| | |
|---|---|
| Status | TODO |
| Milestone | M0 |
| Tier | Human (Claude hỗ trợ xác minh) |
| Phụ thuộc | — |

## Mục tiêu
Visual Studio 2026 build được project C++ UE 5.8.

## Các bước (bạn làm)
1. Mở **Visual Studio Installer** → Modify VS Community 2026.
2. Tab Workloads: tick **Game development with C++**. Trong Installation details bên phải, đảm bảo có tick **Unreal Engine installer** / **Unreal Engine Test Adapter** (tuỳ chọn) và **Windows 11 SDK** mới nhất.
3. Tab Individual components: tìm "MSVC" — cài thêm toolset mà Epic ghi trong **release notes UE 5.8** (mục "Platform SDK Upgrades" → Windows → Visual Studio). Nếu release notes yêu cầu toolset khác 14.51 thì cài đúng toolset đó.
4. Cài xong → khởi động lại máy.
5. Nhờ Claude chạy kiểm tra: "Kiểm tra T-001: liệt kê MSVC toolset và Windows SDK đã cài".

## Tiêu chí hoàn thành
- [ ] Workload "Game development with C++" đã cài.
- [ ] MSVC toolset khớp release notes UE 5.8 (ghi phiên bản vào `docs/05_HARDWARE_AND_DISK.md` §1).
- [ ] T-003 tạo project C++ và build PASS (xác nhận cuối cùng).

---
## Handoff
- MSVC:
- Windows SDK:
