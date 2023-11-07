package main

import (
	"archive/zip"
	"io"
	"os"
	"path/filepath"
)

func main() {
	baseDir := os.Args[1]
	file, err := os.Create("bundle.zip")
	if err != nil {
		panic(err)
	}
	defer file.Close()

	w := zip.NewWriter(file)
	defer w.Close()

	walker := func(baseDir, path string, info os.FileInfo, err error) error {
		if err != nil {
			return err
		}
		if info.IsDir() {
			return nil
		}

		relPath, err := filepath.Rel(baseDir, path)
		if err != nil {
			return err
		}

		file, err := os.Open(path)
		if err != nil {
			return err
		}
		defer file.Close()

		f, err := w.Create(relPath)
		if err != nil {
			return err
		}

		_, err = io.Copy(f, file)
		if err != nil {
			return err
		}

		return nil
	}

	err = filepath.Walk(baseDir, func(path string, info os.FileInfo, err error) error {
		return walker(baseDir, path, info, err)
	})

	if err != nil {
		panic(err)
	}
}
