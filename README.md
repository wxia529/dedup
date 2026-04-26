# dedup

A simple command-line tool to remove duplicate lines from text files while preserving the original order.

## Features

- Remove duplicate lines from input files
- Preserve original line order
- Optional `--info` mode to display repeated line statistics
- Handle both Unix and Windows line endings

## Build

```bash
./configure
make
```

You can also pass options to `configure`:
```bash
./configure --prefix=/usr --cxx=g++
```

## Usage

```bash
# Remove duplicates and output to stdout
./dedup input.txt

# Show repeated lines information
./dedup --info input.txt

# Display help
./dedup --help
```

## License

MIT License - see [LICENSE](LICENSE) for details.
