import os
import sys
import json
import matplotlib.pyplot as plt

def plot_points(data):

    if not isinstance(data, dict) or 'points' not in data or not isinstance(data['points'], list):
        print("Error: Invalid JSON structure.", file=sys.stderr)
        sys.exit(1)

    fig, ax = plt.subplots()

    groups = {}
    for idx, point in enumerate(data['points']):
        group = point.get('group', 'unknown')
        x = point.get('x', 0)
        y = point.get('y', 0)

        if group not in groups:
            groups[group] = []
        groups[group].append((x, y))

    for group, points in groups.items():
        xs, ys = zip(*points)
        ax.scatter(xs, ys, label=f'Group {group}')

    ax.legend()
    plt.title('Scatter Plot of Points')
    plt.xlabel('X')
    plt.ylabel('Y')

    output_dir = "output"
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
    else:
        for filename in os.listdir(output_dir):
            file_path = os.path.join(output_dir, filename)
            try:
                if os.path.isfile(file_path):
                    os.unlink(file_path)
            except Exception as e:
                print(f"Error cleaning output directory: {e}", file=sys.stderr)
                sys.exit(1)

    output_path = os.path.join(output_dir, "output.png")
    plt.savefig(output_path)
    plt.close()

    print(f"Graph saved to {output_path}")

if __name__ == "__main__":
    input_data = sys.stdin.read().strip()
    if not input_data:
        print("Error: No data received from C++ program.", file=sys.stderr)
        sys.exit(1)

    try:
        data = json.loads(input_data)
        if not isinstance(data, dict) or 'points' not in data or not isinstance(data['points'], list):
            print("Error: Invalid JSON structure.", file=sys.stderr)
            sys.exit(1)
        plot_points(data)
    except json.JSONDecodeError as e:
        print(f"Error: Invalid JSON received: {e}", file=sys.stderr)
        sys.exit(1)
