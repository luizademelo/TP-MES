// Copyright 2019 The gRPC Authors

package http2interop

import (
	"path"
	"runtime"
	"strings"
	"sync"
	"testing"
)

func Report(t testing.TB) {

	pcs := make([]uintptr, 10)
	total := runtime.Callers(1, pcs)
	var name string
	for _, pc := range pcs[:total] {
		fn := runtime.FuncForPC(pc)
		fullName := fn.Name()
		if strings.HasPrefix(path.Ext(fullName), ".Test") {

			name = string([]byte(path.Ext(fullName))[1:])
			break
		}
	}
	if name == "" {
		return
	}

	allCaseInfos.lock.Lock()
	defer allCaseInfos.lock.Unlock()
	allCaseInfos.Cases = append(allCaseInfos.Cases, &caseInfo{
		Name:    name,
		Passed:  !t.Failed() && !t.Skipped(),
		Skipped: t.Skipped(),
		Fatal:   t.Failed() && !strings.HasPrefix(name, "TestSoon"),
	})
}

type caseInfo struct {
	Name    string `json:"name"`
	Passed  bool   `json:"passed"`
	Skipped bool   `json:"skipped,omitempty"`
	Fatal   bool   `json:"fatal,omitempty"`
}

type caseInfos struct {
	lock  sync.Mutex
	Cases []*caseInfo `json:"cases"`
}

var (
	allCaseInfos = caseInfos{}
)
