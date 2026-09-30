# T-001 — Toolchain C++ cho UE 5.8

| | |
|---|---|
| Status | IN_PROGRESS |
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
- MSVC: 14.51.36231 (VS Community 2026 18.10.3). Nguồn đối chiếu: `UE_5.8/Engine/Config/Windows/Windows_SDK.json` — Preferred 14.50.35717+ / 14.44.35207+; Banned 14.50.0-14.50.35722, 14.44.0-14.44.35210, 14.40-14.43, 14.39; Minimum 14.38.33130. 14.51 hợp lệ nhưng không nằm trong Preferred.
- Windows SDK: 10.0.26100.0 (UE: MainVersion 10.0.22621.0, Min 10.0.19041.0, Max 10.9.99999.0 → hợp lệ, không phải bản "main").
- Workload NativeGame: đã cài (vswhere xác nhận).
- Còn lại: T-003 build PASS mới đóng T-001. Nếu lỗi toolchain → cài component `Microsoft.VisualStudio.Component.VC.14.50.18.0.x86.x64`.
