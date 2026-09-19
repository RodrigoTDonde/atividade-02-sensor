"""Salva a serial real do Wokwi em evidencias/serial.log (requer pyserial)."""
import argparse
from pathlib import Path
import time

import serial


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--seconds", type=int, default=30)
    args = parser.parse_args()
    output = Path(__file__).resolve().parents[1] / "evidencias" / "serial.log"
    output.parent.mkdir(exist_ok=True)
    print("Conectando ao Wokwi. Mantenha a aba do simulador visivel.", flush=True)
    with serial.serial_for_url("rfc2217://localhost:4000", baudrate=115200, timeout=1) as port:
        deadline = time.monotonic() + args.seconds
        with output.open("a", encoding="utf-8") as log:
            log.write("\n--- Captura serial real: " + time.strftime("%Y-%m-%d %H:%M:%S") + " ---\n")
            while time.monotonic() < deadline:
                line = port.readline().decode("utf-8", errors="replace")
                if line:
                    log.write(line)
                    log.flush()
                    print(line, end="", flush=True)
    print(f"\nCaptura salva: {output}")


if __name__ == "__main__":
    main()
