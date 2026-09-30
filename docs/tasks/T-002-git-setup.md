# T-002 — Git + Git LFS setup

| | |
|---|---|
| Status | REVIEW |
| Milestone | M0 |
| Tier | B |
| Gợi ý model | GPT Luna 6 hoặc Gemini Flash 3.8 |
| Phụ thuộc | — |
| Branch | (làm trực tiếp trên `main` — đây là commit đầu tiên) |

## Mục tiêu
Repo git khởi tạo tại `C:/Users/ADMIN/Downloads/GAME_TEST`, LFS theo dõi file binary Unreal, bỏ qua file sinh ra.

## Đọc trước
- `AGENTS.md`, `docs/DECISIONS.md` (ADR-009), `docs/05_HARDWARE_AND_DISK.md` §2–§4

## Được phép sửa / tạo
- `.gitignore` (root)
- `.gitattributes` (root)
- Chạy lệnh: `git init -b main`, `git lfs install --local`, `git add`, `git commit`

## Cấm
- Không `git push`. Không thêm remote (con người quyết định remote).
- Không tạo file nào khác.

## Các bước
1. `git init -b main` rồi `git lfs install --local`.
2. Tạo `.gitignore` với **đúng** các mục sau (có thể thêm comment):
   ```
   # Unreal generated
   Unreal/Binaries/
   Unreal/DerivedDataCache/
   Unreal/Intermediate/
   Unreal/Saved/
   Unreal/Build/
   Unreal/Plugins/*/Binaries/
   Unreal/Plugins/*/Intermediate/
   Unreal/.vs/
   Unreal/*.sln
   Unreal/*.VC.db
   Unreal/*.opensdf
   Unreal/*.sdf
   Unreal/*.suo
   Unreal/*.xcodeproj
   Unreal/*.xcworkspace
   Unreal/.vsconfig
   # IDE / OS
   .vs/
   .vscode/
   .idea/
   *.DotSettings.user
   Thumbs.db
   Desktop.ini
   .DS_Store
   # Art source lives outside the repo (ADR-009)
   ArtSource/
   *.blend1
   ```
3. Tạo `.gitattributes`:
   ```
   * text=auto
   *.cpp text eol=crlf
   *.h   text eol=crlf
   *.cs  text eol=crlf
   *.ini text eol=crlf
   *.md  text eol=lf
   *.py  text eol=lf
   *.sh  text eol=lf

   *.uasset filter=lfs diff=lfs merge=lfs -text lockable
   *.umap   filter=lfs diff=lfs merge=lfs -text lockable
   *.fbx    filter=lfs diff=lfs merge=lfs -text
   *.png    filter=lfs diff=lfs merge=lfs -text
   *.tga    filter=lfs diff=lfs merge=lfs -text
   *.exr    filter=lfs diff=lfs merge=lfs -text
   *.wav    filter=lfs diff=lfs merge=lfs -text
   *.ogg    filter=lfs diff=lfs merge=lfs -text
   *.ttf    filter=lfs diff=lfs merge=lfs -text
   *.otf    filter=lfs diff=lfs merge=lfs -text
   ```
4. `git add -A` rồi `git status` — kiểm tra chỉ có: `AGENTS.md`, `CLAUDE.md`, `GEMINI.md`, `README.md`, `.gitignore`, `.gitattributes`, `docs/**`.
5. Commit với message chính xác:
   ```
   chore: initial repo with docs kit, gitignore, gitattributes
   ```

## Tiêu chí hoàn thành
- [x] `git lfs track` liệt kê `*.uasset` và `*.umap` có `lockable`.
- [x] `git log --oneline` có đúng 1 commit.
- [x] `git status` sạch.

## Câu hỏi / Blocker

- Không có blocker đối với cấu hình và commit. Lưu ý môi trường: `.git` được
  khởi tạo dưới tài khoản sandbox `CodexSandboxOffline`; Git chạy dưới tài khoản
  `ADMIN` báo `detected dubious ownership` nếu không có ngoại lệ. Các lệnh ghi
  đã dùng `git -c safe.directory=C:/Users/ADMIN/Downloads/GAME_TEST -C
  C:/Users/ADMIN/Downloads/GAME_TEST ...`; ngoại lệ chỉ áp dụng cho từng lệnh,
  không sửa cấu hình toàn cục hay quyền sở hữu thư mục.

---
## Handoff
- File đã tạo: `.gitignore`, `.gitattributes` ở root, đúng nội dung task card.
- File đã cập nhật: task card này (tiêu chí, Status và Handoff theo `AGENTS.md`).
- Repo: khởi tạo `main`, cài Git LFS bằng `git lfs install --local`, stage đúng
  20 file thuộc danh sách cho phép ở bước 4. Không thêm remote, không push.
- Output `git lfs track`:
  ```text
  Listing tracked patterns
      *.uasset [lockable] (.gitattributes)
      *.umap [lockable] (.gitattributes)
      *.fbx (.gitattributes)
      *.png (.gitattributes)
      *.tga (.gitattributes)
      *.exr (.gitattributes)
      *.wav (.gitattributes)
      *.ogg (.gitattributes)
      *.ttf (.gitattributes)
      *.otf (.gitattributes)
  Listing excluded patterns
  ```
- Output log, dùng `git log --oneline --format=%s` để không ghi hash của chính
  commit chứa handoff này:
  ```text
  chore: initial repo with docs kit, gitignore, gitattributes
  ```
- `git rev-list --count HEAD`: `1`. `git status --porcelain`: không có output.
  Handoff được bổ sung bằng amend commit đầu tiên để giữ đúng một commit.
- Kiểm tra: PASS — 25/25 đường dẫn mẫu được ignore; file tài liệu/cấu hình vẫn
  được theo dõi; `git check-attr` xác nhận LFS và `lockable` cho cả `.uasset` và
  `.umap`; `git diff --cached --check` không báo lỗi.
- Build: không áp dụng — chưa có `Unreal/Eclipse.uproject`, task không sửa C++.
- CHƯA XÁC MINH: upload/download và khóa asset trên remote; chưa có remote hoặc
  asset binary thực tế. Các kiểm tra attribute chỉ dùng đường dẫn mẫu, không
  tạo/sửa `.uasset` hay `.umap`.
- Việc con người cần làm trong Editor: không có.
- Khi dùng Git bằng tài khoản `ADMIN`, có thể kiểm tra repo bằng lệnh:
  ```powershell
  git -c safe.directory=C:/Users/ADMIN/Downloads/GAME_TEST -C C:/Users/ADMIN/Downloads/GAME_TEST status
  ```
  Chủ dự án quyết định xử lý quyền sở hữu/ngoại lệ lâu dài và remote sau review.
