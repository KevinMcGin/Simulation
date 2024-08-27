package main

import( 
	"fmt"
	"os"
	"os/exec"
	"time"
	"strconv"
	"encoding/json"
	"log"
	"net/http"
)


func main() {
	fmt.Println("Test server starting...")
	// Define routes
    http.HandleFunc("/api/test/{commitId}/commit", testFunc)

    // Start the server
    log.Fatal(http.ListenAndServe("127.0.0.1:9000", nil))
}

func testFunc(w http.ResponseWriter, r *http.Request) {
	commitId := r.PathValue("commitId")
	testResult := TestResult {
		false,
		"",
	}
	if validateCommmitId(commitId) {
		testResult = runTestsAndGetResult(commitId)
	} else {
		testResult = TestResult {
			false,
			"Invalid commit id",
		}
	}
    w.Header().Set("Content-Type", "application/json")
	jsonBytes, err := json.Marshal(testResult)
	if err != nil {
		fmt.Println("Error marshalling json: %s", err)
	}
	fmt.Println(testResult)
	w.WriteHeader(http.StatusOK)
	w.Write(jsonBytes)
}

func runTestsAndGetResult(commitId string) TestResult {
	fmt.Println("Running tests for commit id:", commitId)

	folderName := pullDownCode(commitId)

	testResult := runTests(folderName)
	deleteFolder(folderName)
	return testResult
}

func validateCommmitId(commitId string) bool {
	out, err := exec.Command("bash", "-c", "git cat-file commit " + commitId).Output()
	if err != nil {
		fmt.Println("Error validating commit: ", commitId, " ", out, err)
		fmt.Println(err)
	}
	return err == nil
}

func pullDownCode(commitId string) string {
	// Todo: get the timestamp
	folderName := strconv.FormatInt(time.Now().Unix(), 10)
	err := os.Mkdir("test_area/" + folderName, os.ModePerm)
	if err != nil {
		fmt.Println("Error creating folder: ", err)
		fmt.Println(err)
	}
	out, err := exec.Command("bash", "-c", "cd test_area/" + folderName + " && git clone https://github.com/KevinMcGin/Simulation.git").Output()
	if err != nil {
		fmt.Println("Error cloning repo: ", out, err)
	}	
	out, err = exec.Command("bash", "-c", "cd test_area/" + folderName + "/Simulation && git checkout " + commitId).Output()
	if err != nil {
		fmt.Println("Error checking out commit: ", out, err)
	}
	out, err = exec.Command("bash", "-c", "cd test_area/" + folderName + "/Simulation && rm config/project.config.example && mv config/gpu_project.config.example config/project.config.example").Output()
	if err != nil {
		fmt.Println("Error renaming project.config: ", out, err)
	}
	return folderName
}

func runTests(folderName string) TestResult {
	out, err := exec.Command("bash", "-c", "cd test_area/" + folderName + "/Simulation/scripts && ./test.sh").Output()
	succeeded := err == nil
	if !succeeded {
		fmt.Println("Tests failed:\n ", err, out)
	}
	testMessage := string(out)
	return TestResult {
		succeeded,
		testMessage,
	}
}

func deleteFolder(folderName string) {
	out, err := exec.Command("bash", "-c", "rm -rf test_area/" + folderName).Output()
	if err != nil {
		fmt.Println("Error deleting folder: ", out, err)
	}
}

type TestResult struct {
    Succeeded bool `json:"succeeded"`
    Message string `json:"message"`
}