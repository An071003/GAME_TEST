#!/usr/bin/env bash
set -u

# Resolve repo root directory
ROOT="$(cd "$(dirname "$0")/.." && pwd)"

# Helper to check and print disk usage
print_entry() {
    local target="$1"
    local note="${2:-}"
    if [ -n "$target" ] && [ -e "$target" ]; then
        local size
        size="$(du -sh "$target" 2>/dev/null | cut -f1)"
        if [ -n "$note" ]; then
            printf "%-8s %s %s\n" "$size" "$target" "$note"
        else
            printf "%-8s %s\n" "$size" "$target"
        fi
    else
        if [ -n "$note" ]; then
            printf "%-8s %s %s\n" "-" "${target:+$target }(không có)" "$note"
        else
            printf "%-8s %s\n" "-" "${target:+$target }(không có)"
        fi
    fi
}

# Resolve LOCALAPPDATA safely
LOCAL_APP="${LOCALAPPDATA:-}"

# 1. Unreal/Content
print_entry "$ROOT/Unreal/Content"

# 2. Unreal/DerivedDataCache
print_entry "$ROOT/Unreal/DerivedDataCache"

# 3. Unreal/Intermediate
print_entry "$ROOT/Unreal/Intermediate"

# 4. Unreal/Saved
print_entry "$ROOT/Unreal/Saved"

# 5. Unreal/Binaries
print_entry "$ROOT/Unreal/Binaries"

# 6. Total .git
print_entry "$ROOT/.git" "(tổng)"

# 7. Git LFS objects
print_entry "$ROOT/.git/lfs"

# 8. Zen cache
if [ -n "$LOCAL_APP" ]; then
    ZEN_PATH="$LOCAL_APP/UnrealEngine/Common/Zen/Data"
else
    ZEN_PATH=""
fi
print_entry "$ZEN_PATH" "(Zen DDC, trần 25 GB - T-004)"

# 9. Google Drive cache
if [ -n "$LOCAL_APP" ]; then
    DRIVE_PATH="$LOCAL_APP/Google/DriveFS"
else
    DRIVE_PATH=""
fi
print_entry "$DRIVE_PATH"

# Print free space on C: drive
df -h /c | tail -1

# Warn and exit 2 if free disk space is less than 30 GB
FREE_GB="$(df -BG /c | tail -1 | awk '{print $4}' | tr -d 'G')"
if [ "$FREE_GB" -lt 30 ]; then
    echo "CẢNH BÁO: ổ C: còn dưới 30 GB — dừng thêm asset, dọn dẹp (05_HARDWARE_AND_DISK.md §2)"
    exit 2
fi

exit 0
