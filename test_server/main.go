package main

import "fmt"
import "os"
import "os/exec"

func main() {
	commitId := "605dcab514c0a471dd9d2ea57946d740fc44bbd9"
	testResult := runTestsAndGetResult(commitId)
	fmt.Println(testResult)
}

func runTestsAndGetResult(commitId string) TestResult {
	fmt.Println("Running tests for commit:", commitId)

	folderName := pullDownCode(commitId)

	out, err := exec.Command("bash", "-c", "cd test_area/" + folderName + "/Simulation/scripts && ./test.sh").Output()
	succeeded := err == nil
	if !succeeded {
		fmt.Println("Tests failed:\n ", err)
	}
	testMessage := string(out)
	exec.Command("bash", "-c", "cd ../..")
	deleteFolder(folderName)
	return TestResult {
		succeeded,
		testMessage,
	}
}

func pullDownCode(commitId string) string {
	// Todo: get the timestamp
	folderName := "timestamp"
	err := os.Mkdir("test_area/" + folderName, os.ModePerm)
	if err != nil {
		fmt.Println("Error creating folder: %s", err)
		fmt.Println(err)
	}
	_, err = exec.Command("bash", "-c", "cd test_area/" + folderName + " && git clone https://github.com/KevinMcGin/Simulation.git").Output()
	if err != nil {
		fmt.Println("Error cloning repo: %s", err)
	}	
	return folderName
}

func deleteFolder(folderName string) {
	exec.Command("bash", "-c", "rm -rf", "test_area/" + folderName).Output()
}

type TestResult struct {
    succeeded bool
    message string
}