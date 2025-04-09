import os
import sys
import matplotlib.pyplot as plt
from collections import defaultdict
from pathlib import Path

def get_language(ext):
    return {'.cpp':'C++', '.c':'C', '.rs':'Rust', 
            '.py':'Python', '.hs':'Haskell'}.get(ext, 'Unknown')

def count_lines(path):
    try:
        return sum(1 for _ in open(path, errors='ignore'))
    except Exception as e:
        print(f"Error reading {path}: {e}")
        return 0

def find_solutions(root):
    solutions = []
    for entry in Path(root).iterdir():
        if entry.is_dir() and entry.name.startswith('P'):
            try:
                problem = int(entry.name[1:])
                for file in entry.rglob('*'):
                    if file.suffix.lower() in {'.cpp', '.c', '.rs', '.py', '.hs'}:
                        solutions.append((
                            problem,
                            get_language(file.suffix.lower()),
                            count_lines(file)
                        ))
            except ValueError:
                continue
    return solutions

def create_plots(data):
    if not data:
        print("No solutions found!")
        return

    plt.figure(figsize=(12, 6))
    plt.suptitle("Project Euler Solutions", y=0.95)
    
    # Language distribution
    lang_counts = defaultdict(int)
    for _, lang, _ in data:
        lang_counts[lang] += 1
    
    # Use qualitative color scheme
    cmap = plt.get_cmap('Pastel1')
    langs, counts = zip(*sorted(lang_counts.items(), key=lambda x: -x[1]))
    
    # Bar chart instead of pie for simplicity
    plt.subplot(121)
    bars = plt.bar(langs, counts, color=cmap(range(len(langs))))
    plt.title('Solutions by Language')
    plt.ylabel('Count')
    
    # Add counts on top of bars
    for bar in bars:
        height = bar.get_height()
        plt.text(bar.get_x() + bar.get_width()/2., height,
                 f'{height}', ha='center', va='bottom')

    # Problem timeline
    plt.subplot(122)
    for i, lang in enumerate(langs):
        x = [p[0] for p in data if p[1] == lang]
        y = [p[2] for p in data if p[1] == lang]
        plt.scatter(x, y, color=cmap(i), label=lang, alpha=0.7)
    
    plt.title('Problem Size Timeline')
    plt.xlabel('Problem Number')
    plt.ylabel('Lines of Code')
    plt.legend()
    plt.grid(True, alpha=0.3)

    # Footer stats
    total_problems = len({p[0] for p in data})
    total_lines = sum(p[2] for p in data)
    plt.figtext(0.5, 0.01, 
                f"Total Problems: {total_problems} | Solutions: {len(data)} | Lines: {total_lines:,}",
                ha='center', fontsize=10)

    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    root = sys.argv[1] if len(sys.argv) > 1 else os.getcwd()
    if not Path(root).is_dir():
        print(f"Invalid directory: {root}")
        sys.exit(1)
    
    create_plots(find_solutions(root))
