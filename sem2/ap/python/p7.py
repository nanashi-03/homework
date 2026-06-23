import os
from typing import Generator


def findfiles_classic(directory: str) -> Generator[str, None, None]:
    """Recursively finds all files using the os module."""
    for root, dirs, files in os.walk(directory):
        for file in files:
            yield os.path.join(root, file)


for file_path in findfiles_classic("."):
    print(file_path)
