import subprocess
import os
import sys

def run_tests():
    executable = "./browser_test"

    # 1. Check if executable exists
    if not os.path.isfile(executable):
        print(f"❌ Error: Executable {executable} not found.")
        sys.exit(1)

    # 2. Start the C process
    process = subprocess.Popen(
        [executable],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )

    print(f"🚀 Starting Test Runner against {executable}...\n")

    # 3. Define commands EXACTLY as main.c expects them
    # Format: (Command to send, Expected Output)
    tests = [
        ("START leetcode.com", "null"),
        ("VISIT google.com",   "null"),
        ("VISIT facebook.com", "null"),
        ("VISIT youtube.com",  "null"),
        ("BACK 1",             "facebook.com"),
        ("BACK 1",             "google.com"),
        ("FORWARD 1",          "facebook.com"),
        ("VISIT linkedin.com", "null"),
        ("FORWARD 2",          "linkedin.com"),
        ("BACK 2",             "google.com"),
        ("EXIT",               None) # EXIT doesn't return an output line
    ]

    all_passed = True

    try:
        for command, expected in tests:
            # Send the command
            print(f"➡️  Input: {command}")
            process.stdin.write(command + "\n")
            process.stdin.flush()

            # If it's EXIT, we don't wait for output, we just break
            if command == "EXIT":
                break

            # Read the response
            actual = process.stdout.readline().strip()

            # Check if C program crashed/closed early
            if not actual and process.poll() is not None:
                print("❌ Error: C program exited prematurely.")
                all_passed = False
                break

            # Compare results
            if actual == expected:
                print(f"   ✅ PASS (Got: {actual})")
            else:
                print(f"   ❌ FAIL (Expected: {expected}, Got: {actual})")
                all_passed = False

    except Exception as e:
        print(f"\n⚠️ Error during execution: {e}")
        all_passed = False

    # cleanup
    process.terminate()

    if all_passed:
        print("\n🎉 ALL TESTS PASSED!")
        sys.exit(0)
    else:
        print("\n💀 SOME TESTS FAILED.")
        sys.exit(1)

if __name__ == "__main__":
    run_tests()