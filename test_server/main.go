package main

import "fmt"
import "os"
import "os/exec"
import "time"
import "strconv"

func main() {
	commitId := "518a9600b12fa01a2aa1b722441640ddfed6b7d5"
	testResult := runTestsAndGetResult(commitId)
	fmt.Println(testResult)
}

func runTestsAndGetResult(commitId string) TestResult {
	fmt.Println("Running tests for commit:", commitId)

	folderName := pullDownCode(commitId)

	testResult := runTests(folderName)
	deleteFolder(folderName)
	return testResult
}

func pullDownCode(commitId string) string {
	// Todo: get the timestamp
	folderName := strconv.FormatInt(time.Now().Unix(), 10)
	err := os.Mkdir("test_area/" + folderName, os.ModePerm)
	if err != nil {
		fmt.Println("Error creating folder: %s", err)
		fmt.Println(err)
	}
	_, err = exec.Command("bash", "-c", "cd test_area/" + folderName + " && git clone https://github.com/KevinMcGin/Simulation.git").Output()
	if err != nil {
		fmt.Println("Error cloning repo: %s", err)
	}	
	_, err = exec.Command("bash", "-c", "cd test_area/" + folderName + "/Simulation && git checkout " + commitId).Output()
	if err != nil {
		fmt.Println("Error checking out commit: %s", err)
	}
	_, err = exec.Command("bash", "-c", "cd test_area/" + folderName + "/Simulation && rm config/project.config.example && mv config/gpu_project.config.example config/project.config.example").Output()
	if err != nil {
		fmt.Println("Error renaming project.config: %s", err)
	}
	return folderName
}

func runTests(folderName string) TestResult {
	out, err := exec.Command("bash", "-c", "cd test_area/" + folderName + "/Simulation/scripts && ./test.sh").Output()
	succeeded := err == nil
	if !succeeded {
		fmt.Println("Tests failed:\n ", err)
	}
	testMessage := string(out)
	return TestResult {
		succeeded,
		testMessage,
	}
}

func deleteFolder(folderName string) {
	err := os.RemoveAll("test_area/" + folderName)
	if err != nil {
		fmt.Println("Error deleting folder: %s", err)
	}
}

type TestResult struct {
    succeeded bool
    message string
}