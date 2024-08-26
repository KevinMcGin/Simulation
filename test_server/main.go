package main

import "fmt"
import "os"
import "os/exec"

func main() {
	commitId := "7a829deae043a3304110168cb231d21d92618d1a"
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
	folderName := "timestamp2"
	err := os.Mkdir("test_area/" + folderName, os.ModePerm)
	if err != nil {
		fmt.Println("Error creating folder: %s", err)
		fmt.Println(err)
	}
	_, err = exec.Command("bash", "-c", "cd test_area/" + folderName + " && git clone https://github.com/KevinMcGin/Simulation.git && git checkout " + commitId).Output()
	if err != nil {
		fmt.Println("Error cloning repo: %s", err)
	}	
	_, err = exec.Command("bash", "-c", "cd test_area/" + folderName + "/Simulation && rm config/project.config.example && mv config/gpu_project.config.example config/project.config.example").Output()
	if err != nil {
		fmt.Println("Error renaming project.config: %s", err)
	}
	return folderName
}

func deleteFolder(folderName string) {
	_, err := exec.Command("bash", "-c", "rm -rf", "test_area/" + folderName).Output()
	if err != nil {
		fmt.Println("Error deleting folder: %s", err)
	}
}

type TestResult struct {
    succeeded bool
    message string
}