USB_VID = 0x239A
USB_PID = 0x8052
USB_PRODUCT = "ItsyBitsy nRF52840 Express"
USB_MANUFACTURER = "Adafruit Industries LLC"

MCU_CHIP = nrf52840

# Don't use up a hardware SPI peripheral for the status DotStar: we only have one or two.
CIRCUITPY_BITBANG_APA102 = 1

QSPI_FLASH_FILESYSTEM = 1
EXTERNAL_FLASH_DEVICE_COUNT = 1
EXTERNAL_FLASH_DEVICES = "GD25Q16C"

FROZEN_MPY_DIRS += $(TOP)/frozen/Adafruit_CircuitPython_DotStar
FROZEN_MPY_DIRS += $(TOP)/frozen/Adafruit_CircuitPython_IL0398
FROZEN_MPY_DIRS += $(TOP)/frozen/Adafruit_CircuitPython_BLE
FROZEN_MPY_DIRS += $(TOP)/frozen/Adafruit_CircuitPython_Display_Shapes
FROZEN_MPY_DIRS += $(TOP)/frozen/Adafruit_CircuitPython_Bitmap_Font
FROZEN_MPY_DIRS += $(TOP)/frozen/Adafruit_CircuitPython_Debouncer
FROZEN_MPY_DIRS += $(TOP)/frozen/Adafruit_CircuitPython_ImageLoad
