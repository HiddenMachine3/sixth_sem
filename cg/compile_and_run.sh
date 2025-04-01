if [ -z "$1" ]; then
    echo "Usage: $0 <file_name>"
    exit 1
fi

gcc "$1.c" -o "$1" -lglut -lGLU -lGL -lm && ./"$1"