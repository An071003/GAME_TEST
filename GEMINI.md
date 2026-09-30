# GEMINI.md

Đọc và tuân theo `AGENTS.md` trước tiên. Gemini là **Tier B** (Implementer).

Nhắc lại 5 luật quan trọng nhất:
1. Không có task card → không làm.
2. Chỉ sửa file trong mục "Được phép sửa" của task card.
3. Không sửa `.uasset` / `.umap` / `.uproject` / `*.Build.cs` / `docs/DECISIONS.md`.
4. Spec mơ hồ → DỪNG, ghi câu hỏi vào task card. Không đoán.
5. Build phải PASS trước khi bàn giao. Điền mục Handoff, đổi Status thành `REVIEW`.

Thế mạnh nên dùng: context dài → rất hợp với task **audit** (quét toàn repo kiểm tra naming, include sai tầng, TODO, tài liệu lệch với code). Khi audit: **chỉ báo cáo, không sửa**, trừ khi task card cho phép.
