# 02 — TEAM WORKFLOW (làm việc như một team AI)

## 1. Đội hình
| Vai | Model | Điểm mạnh | Điểm yếu | Giao việc gì |
|---|---|---|---|---|
| **Tier A — Lead / Architect / Reviewer** | Claude Opus 5.5 | Suy luận, kiến trúc, debug, review | Tốn chi phí/quota hơn | Thiết kế, C++ lõi, bug khó, review, viết task card. Sở hữu tài liệu kiến trúc |
| **Tier A — Lead dự phòng** | Claude Sonnet 5.5 | Như Opus, rẻ hơn | Kém Opus ở bài toán rất khó | Thay Opus khi Opus hết quota / không hoạt động; cũng làm việc Tier A mức vừa |
| **Tier A — Hard-task engineer** | GPT 6.1 (extra high) | Suy luận mạnh, góc nhìn thứ hai | Chưa quen luật repo → phải có task card | C++ lõi theo task card, bug khó, review chéo code của Claude. Không sửa tài liệu kiến trúc (chỉ đề xuất) |
| **Tier B — Implementer** | GPT Luna 6 (extra high) | Viết nhiều, nhanh | Suy luận/logic yếu, dễ "tự sáng tạo" | Điền `.cpp` theo `.h` có sẵn, script Python, config, doc hướng dẫn |
| **Tier B — Implementer / Auditor** | Gemini Flash 3.8 (high) | Nhanh, context dài | Suy luận yếu | Audit toàn repo, dữ liệu (CSV/JSON), doc, tóm tắt tài liệu Epic |
| **Tier I — Image** | GPT 6.1 Sol (extra high) | Tạo ảnh | — | Concept, reference sheet, icon, mood board |
| **Human — Director** | Bạn | Mắt, tay, cảm giác | Thời gian | Editor, Blender, tuning, playtest, merge, quyết định |

## 2. Việc gì giao cho tier nào
### Giao Tier B khi TẤT CẢ điều sau đúng
- Có spec rõ: input, output, file được phép sửa.
- Không cần quyết định kiến trúc.
- Kiểm tra được đúng/sai bằng máy (build pass, test pass, script chạy ra kết quả X) hoặc bằng mắt dễ dàng.
- Nếu sai thì hậu quả nhỏ và dễ revert.

### Ví dụ việc Tier B làm tốt
| Loại | Ví dụ |
|---|---|
| Boilerplate theo mẫu | Tier A viết `EclipseRestPoint.h` → Tier B viết `.cpp` theo comment trong header |
| Config / ini | `.gitignore`, `.gitattributes`, `DefaultInput.ini`, gameplay tag ini cho content |
| Dữ liệu | CSV cho Data Table (stat enemy, bảng level up), JSON attack data để script import |
| Script Python Editor | Tạo hàng loạt Input Action, đổi tên asset theo convention, kiểm tra asset thiếu prefix |
| Script Python Blender | Export FBX theo `COL_EXPORT`, kiểm tra scale = 1, kiểm tra tên bone khớp Mannequin |
| Tài liệu | Hướng dẫn Editor từng bước (có ảnh chụp do bạn bổ sung), glossary, changelog |
| Audit (chỉ báo cáo) | Include sai tầng, asset sai naming, TODO còn sót, doc lệch code |
| Test | Automation test theo test case Tier A đã liệt kê |

### KHÔNG bao giờ giao Tier B
- Thiết kế class mới, sửa header public của hệ thống lõi.
- AttributeSet, ExecutionCalculation, ability base, input buffer, combat component, save system.
- Debug bug mà chưa biết nguyên nhân.
- Bất cứ gì chạm `Build.cs`, `.uproject`, `DECISIONS.md`.
- Bug về timing/animation/networking/GC (UPROPERTY thiếu → crash ngẫu nhiên).

## 3. Mô hình "Tier A viết header, Tier B viết thân hàm"
Hiệu quả nhất để tận dụng model yếu:
1. Tier A viết `.h` hoàn chỉnh: UCLASS, UPROPERTY, chữ ký hàm, và **comment mô tả từng hàm phải làm gì theo từng bước**.
2. Tier A viết task card: "Implement `EclipseRestPoint.cpp` theo comment trong header. Chỉ sửa file `.cpp` này."
3. Tier B viết `.cpp`, build.
4. Tier A review.

## 4. Vòng đời task
```
TODO ──(được giao)──> IN_PROGRESS ──(handoff)──> REVIEW ──(Tier A OK)──> APPROVED ──(bạn merge + test Editor)──> DONE
                          │                          │
                          └──> BLOCKED (câu hỏi)     └──> CHANGES_REQUESTED ──> IN_PROGRESS
```
- Task card: `docs/tasks/T-XXX-ten.md`, dùng mẫu `_TEMPLATE.md`.
- Danh sách tổng: `docs/tasks/BACKLOG.md`.
- Bạn là người đổi `APPROVED → DONE` sau khi tự mở Editor kiểm tra.

## 5. Checklist review của Tier A
- [ ] Chỉ sửa file trong "Được phép sửa"?
- [ ] Build PASS (tự chạy lại, không tin handoff)?
- [ ] Đúng quy tắc include (`01_ARCHITECTURE.md` §3)?
- [ ] Mọi `UObject*` member có `UPROPERTY()` (tránh GC crash)? Dùng `TObjectPtr<>`?
- [ ] Không có string tag rải rác (ADR-010)?
- [ ] Không có magic number gameplay (phải ở Data Asset / UPROPERTY EditDefaultsOnly)?
- [ ] Không có Tick khi không cần?
- [ ] Null check cho pointer từ bên ngoài (owner, ASC, weapon)?
- [ ] Khớp tiêu chí hoàn thành của task card?
- [ ] Có API nào bịa / không tồn tại trong UE 5.8?

**Review chéo Tier A:** code lõi do GPT 6.1 viết → Claude review; code lõi do Claude viết mà rủi ro cao (damage execution, save, input buffer) → có thể nhờ GPT 6.1 review. Không ai tự duyệt code của chính mình.

## 6. Cách ra lệnh cho từng model (copy-paste)
### Cho Tier B (GPT Luna / Gemini Flash)
```
Bạn là Tier B implementer trong repo này.
1. Đọc AGENTS.md, docs/DECISIONS.md.
2. Đọc task card docs/tasks/T-XXX-*.md và mọi tài liệu trong mục "Đọc trước".
3. Tạo branch task/T-XXX-<tên>.
4. Làm ĐÚNG task card. Chỉ sửa file trong "Được phép sửa".
5. Build theo AGENTS.md §4. Sửa lỗi tối đa 3 vòng.
6. Điền mục Handoff, đổi Status thành REVIEW, commit.
Nếu có gì không rõ: DỪNG, ghi vào "Câu hỏi / Blocker", đổi Status thành BLOCKED. Không đoán.
```

### Cho Claude — review
```
Review task T-XXX: so sánh branch task/T-XXX-* với main theo checklist docs/02_TEAM_WORKFLOW.md §5.
Chạy build. Kết luận APPROVED hoặc CHANGES_REQUESTED kèm danh sách sửa cụ thể.
```

### Cho Claude — lập kế hoạch milestone
```
Đọc docs/00_MASTER_PLAN.md và docs/tasks/BACKLOG.md. Tách milestone Mx thành task card.
Gán tier theo docs/02_TEAM_WORKFLOW.md §2. Với task Tier B: viết sẵn header và tiêu chí kiểm tra được.
```

### Cho GPT 6.1 (extra high) — việc khó
```
Bạn là Tier A hard-task engineer trong repo này.
1. Đọc AGENTS.md, docs/DECISIONS.md, docs/01_ARCHITECTURE.md.
2. Đọc task card docs/tasks/T-XXX-*.md và mọi tài liệu trong mục "Đọc trước".
3. Làm đúng task card, build theo AGENTS.md §4.
4. Không sửa docs/01_ARCHITECTURE.md, docs/DECISIONS.md, *.Build.cs, .uproject, EclipseGameplayTags.*.
   Cần đổi → ghi đề xuất vào DECISIONS.md mục "Đề xuất chờ duyệt".
5. Điền Handoff, đổi Status thành REVIEW. Claude sẽ review chéo.
```

### Khi Opus không hoạt động
Mở Claude Code, chọn Sonnet 5.5 (`/model`), dùng đúng các lệnh ở trên. Sonnet có mọi quyền của Lead.

### Cho GPT Sol — ảnh
Xem `06_ART_PIPELINE.md` §5.

## 7. Chạy song song
- Tier B có thể làm 2–3 task cùng lúc **nếu các task không sửa chung file**. Task card ghi rõ "Không chạy song song với: T-xxx" khi cần.
- Tier A không bao giờ bị chặn bởi Tier B: Tier A làm việc lõi của milestone kế tiếp trong khi Tier B điền phần boilerplate.
- Bạn làm việc Editor/Blender song song với cả hai.

## 8. Khi Tier B làm hỏng
- Không cố "vá" bằng Tier B lần nữa quá 1 lần. Lần thứ 2 hỏng → chuyển task sang Tier A hoặc chia nhỏ task.
- Ghi lại lý do hỏng vào cuối task card (mục "Bài học") → Tier A cải thiện cách viết task card sau.
