# AGENTS.md — Luật chung cho MỌI AI agent làm việc trong repo này

Dự án: **Eclipse** — third-person action RPG / Soulslike, single-player.
Engine: Unreal Engine 5.8 (C++ + Blueprint + GAS). Art: Blender 4.5.
Chủ dự án (con người) là người quyết định cuối cùng và là người duy nhất thao tác trong Unreal Editor.

---

## 0. Trước khi làm bất cứ việc gì
1. Đọc file này hết.
2. Đọc `docs/DECISIONS.md` (các quyết định đã chốt — KHÔNG được đảo ngược).
3. Đọc **task card** bạn được giao trong `docs/tasks/`. Không có task card → không làm.
4. Đọc các tài liệu mà task card liệt kê ở mục "Đọc trước".

## 1. Phân tầng agent (xem chi tiết `docs/02_TEAM_WORKFLOW.md`)
| Tier | Model | Được làm |
|---|---|---|
| **A** — Architect / Lead | Claude (Opus 5.5 / sonnet 5.5) | Kiến trúc, C++ lõi, GAS, AI framework, save, debug, **review mọi diff của Tier B**, viết task card |
| **B** — Implementer | GPT Luna 6 (extra high), Gemini Flash 3.8 (high) | Task đã có spec chi tiết: boilerplate theo mẫu, config, dữ liệu, script Python, tài liệu hướng dẫn, audit |
| **I** — Image | GPT 6.1 Sol | Concept art, reference sheet, icon, mood board |
| **Human** | Chủ dự án | Mọi thao tác trong Unreal Editor & Blender, playtest, merge |

Nếu bạn là Tier B: **bạn chỉ làm đúng task card**. Không "cải thiện" thêm, không refactor ngoài phạm vi.

## 2. Luật cứng (vi phạm = diff bị từ chối)
1. **Chỉ sửa file nằm trong mục "Được phép sửa" của task card.** Cần sửa file khác → DỪNG, ghi câu hỏi vào mục "Câu hỏi / Blocker" của task card.
2. **Không bao giờ sửa/tạo/xóa file `.uasset`, `.umap`** (file binary; chỉ con người sửa qua Editor).
3. **Không sửa** các file sau trừ khi task card cho phép rõ ràng:
   - `Unreal/Eclipse.uproject`, `*.Build.cs`, `*.Target.cs`
   - `Unreal/Config/DefaultEngine.ini`, `DefaultGame.ini`
   - `docs/DECISIONS.md`, `AGENTS.md`, `docs/01_ARCHITECTURE.md`
   - `Source/Eclipse/Core/EclipseGameplayTags.*`
4. **Không bật/tắt plugin. Không thêm thư viện ngoài.**
5. **Không đổi tên/di chuyển class, file, hàm public đã có.**
6. **Không đoán.** Spec mơ hồ → dừng và hỏi. Một câu hỏi tốt hơn 500 dòng code sai.
7. **Không bịa API.** Nếu không chắc một hàm Unreal có tồn tại ở UE 5.8 → ghi rõ "CHƯA XÁC MINH" trong handoff, không giả vờ chắc chắn.
8. **Không xóa file** ngoài phạm vi task. Không chạy `git reset --hard`, `git clean`, `git push --force`.
9. Code phải **build được** trước khi bàn giao (xem mục 4). Không build được → ghi lỗi vào handoff, không bàn giao như "xong".

## 3. Quy tắc phụ thuộc code (tóm tắt — đầy đủ ở `docs/01_ARCHITECTURE.md`)
```
Core  ←  Abilities  ←  Combat  ←  Characters  ←  AI
  ↑                                    ↑
  └──────────── Inventory ─────────────┘
UI  → chỉ đọc (subscribe event / delegate). Không ai include UI/.
World, Save → dùng Core + interfaces, không include Characters trực tiếp.
```
- `Combat/`, `Abilities/`, `Characters/` **không bao giờ** `#include` bất cứ thứ gì trong `UI/`.
- Giao tiếp chéo hệ thống qua **interface** (`IEclipseDamageable`...) hoặc **event** (`UEclipseEventSubsystem`).

## 4. Build & kiểm tra
```bash
"/c/Program Files/Epic Games/UE_5.8/Engine/Build/BatchFiles/Build.bat" EclipseEditor Win64 Development \
  -Project="C:/Users/ADMIN/Downloads/GAME_TEST/Unreal/Eclipse.uproject" -WaitMutex -NoHotReloadFromIDE
```
- Đóng Unreal Editor trước khi build (hoặc dùng Live Coding trong Editor — do con người thực hiện).
- Build lỗi → đọc lỗi ĐẦU TIÊN, sửa, build lại. Tối đa 3 vòng; sau đó dừng và ghi vào handoff.

## 5. Quy ước (tóm tắt — đầy đủ ở `docs/03_CONVENTIONS.md`)
- Class C++: tiền tố Unreal + `Eclipse` → `AEclipsePlayerCharacter`, `UEclipseCombatComponent`, `IEclipseDamageable`.
- Asset: `BP_`, `SM_`, `SK_`, `GA_`, `GE_`, `DA_`, `AM_`, ... (bảng đầy đủ trong conventions).
- 1 Unreal Unit = 1 cm. Asset import scale = 1.
- Comment code bằng tiếng Anh, ngắn gọn. Tài liệu `docs/` bằng tiếng Việt.

## 6. Bàn giao (Handoff)
Khi xong, điền mục **Handoff** ở cuối task card:
- Đã sửa/tạo những file nào
- Build: PASS / FAIL (dán lỗi nếu FAIL)
- Những gì CHƯA làm / CHƯA XÁC MINH
- Việc con người cần làm trong Editor (nếu có), viết từng bước
Sau đó đổi `Status:` của task card thành `REVIEW`.

## 7. Git
- Mỗi task một branch: `task/T-012-ten-ngan`.
- Commit message: `T-012: mô tả ngắn`.
- Không merge vào `main`. Tier A review → con người merge.
