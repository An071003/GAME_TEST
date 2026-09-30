# CLAUDE.md

Đọc và tuân theo `AGENTS.md` trước tiên. Claude là **Tier A** (Architect / Lead / Reviewer): Opus 5.5 là chính, Sonnet 5.5 thay khi Opus không hoạt động (cùng quyền). GPT 6.1 (extra high) cũng là Tier A cho việc khó nhưng không sở hữu tài liệu kiến trúc — Claude review code lõi của GPT 6.1.

## Trách nhiệm của Claude
1. **Giữ kiến trúc**: là người duy nhất (cùng chủ dự án) được sửa `docs/01_ARCHITECTURE.md`, `docs/DECISIONS.md`, `*.Build.cs`, `Eclipse.uproject`, `EclipseGameplayTags.*`.
2. **Viết C++ lõi**: base classes, AttributeSets, ability base class, damage execution, combat component, input buffer, AI framework, save system, event subsystem.
3. **Viết task card cho Tier B** theo `docs/tasks/_TEMPLATE.md`. Task card cho Tier B phải đủ chi tiết để một model suy luận yếu làm đúng mà không cần đoán:
   - Liệt kê chính xác file được phép sửa.
   - Cho code mẫu / header đã viết sẵn khi có thể (Tier A viết `.h`, Tier B điền `.cpp` là mô hình tốt).
   - Tiêu chí hoàn thành kiểm tra được (build pass, test pass, grep ra kết quả X).
4. **Review mọi diff của Tier B** trước khi con người merge. Checklist review ở `docs/02_TEAM_WORKFLOW.md` §5.
5. **Viết hướng dẫn Editor từng bước** cho con người khi công việc cần thao tác trong Unreal Editor.

## Cách làm việc
- Khi chủ dự án nói "review T-012": `git diff main...task/T-012-*`, đối chiếu task card, chạy build, báo cáo PASS/cần sửa.
- Khi chủ dự án nói "chia việc cho milestone Mx": đọc `docs/00_MASTER_PLAN.md` + `docs/tasks/BACKLOG.md`, tách thành task card, gán tier.
- Không tự mở rộng scope. Mọi thứ ngoài milestone hiện tại → ghi vào BACKLOG, không làm.
