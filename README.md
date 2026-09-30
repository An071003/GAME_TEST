# Eclipse — Soulslike (UE 5.8)

## Bắt đầu từ đâu
| Bạn là | Đọc |
|---|---|
| Chủ dự án | `docs/00_MASTER_PLAN.md` → `docs/tasks/BACKLOG.md` |
| AI agent bất kỳ | `AGENTS.md` → `docs/DECISIONS.md` → task card của bạn |
| Claude | thêm `CLAUDE.md` |
| Gemini | thêm `GEMINI.md` |

## Bản đồ tài liệu
| File | Nội dung |
|---|---|
| `AGENTS.md` | Luật chung cho mọi AI agent |
| `docs/DECISIONS.md` | Quyết định kiến trúc đã chốt (ADR) + lý do sửa kế hoạch gốc |
| `docs/00_MASTER_PLAN.md` | Milestone, scope, tiêu chí hoàn thành |
| `docs/01_ARCHITECTURE.md` | Cấu trúc C++, class, component, quy tắc phụ thuộc |
| `docs/02_TEAM_WORKFLOW.md` | Chia việc giữa các model, vòng đời task, review |
| `docs/03_CONVENTIONS.md` | Naming, thư mục, scale, style C++ |
| `docs/04_COMBAT_GAS_SPEC.md` | Spec combat + GAS (tag, attribute, attack data, damage, poise, dodge, input buffer) |
| `docs/05_HARDWARE_AND_DISK.md` | Giới hạn máy, ngân sách ổ đĩa, VRAM, scalability |
| `docs/06_ART_PIPELINE.md` | Blender → Unreal, dùng model tạo ảnh |
| `docs/tasks/` | Task card + backlog |

## Cấu trúc repo
```
GAME_TEST/
├── AGENTS.md  CLAUDE.md  GEMINI.md  README.md
├── docs/                 # tài liệu + task card
├── Unreal/               # project UE (Eclipse.uproject) — tạo ở task T-003
└── Tools/                # script Python cho Blender / Unreal
```
`ArtSource/` (file .blend, .psd, texture gốc) **nằm ngoài repo** — xem `docs/05_HARDWARE_AND_DISK.md`.
