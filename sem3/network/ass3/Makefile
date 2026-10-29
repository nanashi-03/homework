# Define the default shell
SHELL := /bin/bash

# Dynamically find the absolute path of the parent's .venv directory
VENV := $(shell cd ../.venv && pwd)
PYTHON = $(VENV)/bin/python
PIP = $(VENV)/bin/pip

.DEFAULT_GOAL := help

.PHONY: help venv install test clean %

help:
	@echo "Available commands:"
	@echo "  make venv         - Create a virtual environment in parent directory (../.venv)"
	@echo "  make install      - Install requirements inside the parent .venv"
	@echo "  make test         - Run test suites using pytest (with sudo)"
	@echo "  make run-<file>   - Run any local python file with sudo (e.g., 'make run-exp2')"
	@echo "  make clean        - Remove cached files and build artifacts"

venv:
	@echo "Creating virtual environment in parent directory..."
	python3 -m venv ../.venv
	@echo "Virtual environment created"

install:
	@echo "Installing dependencies..."
	$(PIP) install --upgrade pip
	$(PIP) install -r requirements.txt

# Dynamic rule to run any specific local python file with sudo
run-%:
	@if [ ! -f "$*.py" ]; then echo "Error: $*.py does not exist"; exit 1; fi
	sudo $(PYTHON) $*.py

test:
	sudo $(PYTHON) -m pytest tests/

clean:
	@echo "Cleaning up local workspace artifacts..."
	find . -type d -name "__pycache__" -exec rm -rf {} +
	find . -type d -name "*.egg-info" -exec rm -rf {} +
	find . -type d -name ".pytest_cache" -exec rm -rf {} +
