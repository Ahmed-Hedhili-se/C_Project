import json
import subprocess

def run_tests():

    # 1. Load the JSON file
    with open('tests.json', 'r') as f:
        data = json.load(f)

    # 2. Start your C program in the background
    process = subprocess.Popen(
        ['./browser_test'],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        text=True
    )

    test_case = data['test_cases'][0]
    actions = test_case['actions']
    params = test_case['params']
    expected = test_case['expected']

    print(f"Running: {test_case['name']}\n" + "-"*30)

    # 3. Loop through actions and feed them to C program
    for i, action in enumerate(actions):
        argument = params[i][0] # Get the first argument

        # Send command to C program
        # Example: "browserHistoryVisit google.com\n"
        command_str = f"{action} {argument}\n"
        process.stdin.write(command_str)
        process.stdin.flush()

        # Read result from C program
        actual_output = process.stdout.readline().strip()

        # Check against expected
        expected_output = expected[i]

        # Handle "null" vs None
        if expected_output is None:
            expected_str = "null"
        else:
            expected_str = expected_output

        status = "✅ PASS" if actual_output == expected_str else f"❌ FAIL (Got: {actual_output})"
        print(f"Action: {action:<22} | Expected: {expected_str:<15} | {status}")

    process.terminate()

if __name__ == "__main__":
    run_tests()