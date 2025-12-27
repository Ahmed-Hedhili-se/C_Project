import json
import subprocess
import os

def run_tests():
    # 0. Check if tests.json exists
    if not os.path.isfile('tests.json'):
        print("❌ Error: 'tests.json' not found in the repository.")
        exit(1)

    # 1. Load the JSON file
    with open('tests.json', 'r') as f:
        data = json.load(f)

    # 2. Start your C program
    process = subprocess.Popen(
        ['./browser_test'],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )

    # 3. Define a Translation Map (JSON -> C)
    # This maps the LeetCode style names to your main.c keywords
    command_map = {
        "BrowserHistory": "START",
        "visit":          "VISIT",
        "back":           "BACK",
        "forward":        "FORWARD"
    }

    test_case = data['test_cases'][0]
    actions = test_case['actions']
    params = test_case['params']
    expected = test_case['expected']

    print(f"Running: {test_case['name']}\n" + "-"*30)

    all_passed = True

    try:
        # 4. Loop through actions
        for i, action in enumerate(actions):
            argument = params[i][0] if params[i] else ""

            # TRANSLATE the command
            c_command = command_map.get(action, action)

            # Send command to C program
            command_str = f"{c_command} {argument}\n"
            process.stdin.write(command_str)
            process.stdin.flush()

            # Read result
            actual_output = process.stdout.readline().strip()

            # Prepare expected string
            expected_output = expected[i]
            if expected_output is None:
                expected_str = "null"
            else:
                expected_str = expected_output

            # Compare
            if actual_output == expected_str:
                print(f"✅ Action: {action:<15} | Output: {actual_output}")
            else:
                print(f"❌ Action: {action:<15} | Expected: {expected_str}, Got: '{actual_output}'")
                all_passed = False

    except Exception as e:
        print(f"\n⚠️ Crash or Timeout: {e}")
        all_passed = False

    # 5. Clean up
    # Send EXIT to ensure C program closes (if it supports it)
    try:
        process.stdin.write("EXIT\n")
        process.stdin.flush()
    except:
        pass

    process.terminate()

    if all_passed:
        print("\n🎉 ALL TESTS PASSED!")
        exit(0)
    else:
        print("\n💀 TESTS FAILED")
        exit(1)

if __name__ == "__main__":
    run_tests()