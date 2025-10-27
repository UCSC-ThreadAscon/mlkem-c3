set(mlkem_native_dirs
    "mlkem-native/mlkem"
    "mlkem-native/mlkem/src"
    "mlkem-native/mlkem/src/fips202"
    "mlkem-native/mlkem/src/fips202/native"
    "mlkem-native/mlkem/src/fips202/native/aarch64"
    "mlkem-native/mlkem/src/fips202/native/aarch64/src"
    "mlkem-native/mlkem/src/fips202/native/x86_64"
    "mlkem-native/mlkem/src/fips202/native/x86_64/src"
    "mlkem-native/mlkem/src/native"
    "mlkem-native/mlkem/src/native/aarch64"
    "mlkem-native/mlkem/src/native/aarch64/src"
    "mlkem-native/mlkem/src/native/riscv64"
    "mlkem-native/mlkem/src/native/riscv64/src"
    "mlkem-native/mlkem/src/native/x86_64"
    "mlkem-native/mlkem/src/native/x86_64/src")

idf_component_register(
  SRC_DIRS "${mlkem_native_dirs}"
  INCLUDE_DIRS "${mlkem_native_dirs}")