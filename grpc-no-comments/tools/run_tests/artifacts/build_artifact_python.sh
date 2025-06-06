#!/bin/bash
# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

cd "$(dirname "$0")/../../.."

export GRPC_PYTHON_BUILD_WITH_CYTHON=1
export PYTHON=${PYTHON:-python}
export AUDITWHEEL=${AUDITWHEEL:-auditwheel}

source tools/internal_ci/helper_scripts/prepare_ccache_symlinks_rc

"${PYTHON}" -m pip install --upgrade pip

"${PYTHON}" -m pip install setuptools==69.5.1 wheel==0.43.0

if [ "$GRPC_SKIP_PIP_CYTHON_UPGRADE" == "" ]
then

  "${PYTHON}" -m pip install --upgrade 'cython==3.1.1'
fi

export GRPC_PYTHON_BUILD_EXT_COMPILER_JOBS=${GRPC_PYTHON_BUILD_EXT_COMPILER_JOBS:-2}

mkdir -p "${ARTIFACTS_OUT}"
ARTIFACT_DIR="$PWD/${ARTIFACTS_OUT}"

if [ "$AUDITWHEEL_ARCH" == "aarch64" ]
then

  WHEEL_PLAT_NAME_FLAG="--plat-name=$AUDITWHEEL_PLAT"

  GRPC_PYTHON_OVERRIDE_EXT_SUFFIX="$(${PYTHON} -c 'import sysconfig; print(sysconfig.get_config_var("EXT_SUFFIX").replace("-x86_64-linux-gnu.so", "-aarch64-linux-gnu.so"))')"
  export GRPC_PYTHON_OVERRIDE_EXT_SUFFIX

  export GRPC_BUILD_OVERRIDE_BORING_SSL_ASM_PLATFORM="linux-aarch64"
fi

if [ "$AUDITWHEEL_ARCH" == "armv7l" ]
then

  WHEEL_PLAT_NAME_FLAG="--plat-name=$AUDITWHEEL_PLAT"

  GRPC_PYTHON_OVERRIDE_EXT_SUFFIX="$(${PYTHON} -c 'import sysconfig; print(sysconfig.get_config_var("EXT_SUFFIX").replace("-x86_64-linux-gnu.so", "-arm-linux-gnueabihf.so"))')"
  export GRPC_PYTHON_OVERRIDE_EXT_SUFFIX

  export GRPC_BUILD_OVERRIDE_BORING_SSL_ASM_PLATFORM="linux-arm"
fi

ancillary_package_dir=(
  "src/python/grpcio_admin/"
  "src/python/grpcio_channelz/"
  "src/python/grpcio_csds/"
  "src/python/grpcio_health_checking/"
  "src/python/grpcio_reflection/"
  "src/python/grpcio_status/"
  "src/python/grpcio_testing/"
  "src/python/grpcio_observability/"
  "src/python/grpcio_csm_observability/"
)

for directory in "${ancillary_package_dir[@]}"; do
  cp "LICENSE" "${directory}"
done

${SETARCH_CMD} "${PYTHON}" setup.py sdist

${SETARCH_CMD} "${PYTHON}" setup.py bdist_wheel $WHEEL_PLAT_NAME_FLAG

GRPCIO_STRIP_TEMPDIR=$(mktemp -d)
GRPCIO_TAR_GZ_LIST=( dist/grpcio-*.tar.gz )
GRPCIO_TAR_GZ=${GRPCIO_TAR_GZ_LIST[0]}
GRPCIO_STRIPPED_TAR_GZ=$(mktemp -t "TAR_GZ_XXXXXXXXXX")

clean_non_source_files() {
( cd "$1"
  find . -type f \
    | grep -v '\.c$' | grep -v '\.cc$' | grep -v '\.cpp$' \
    | grep -v '\.h$' | grep -v '\.hh$' | grep -v '\.inc$' \
    | grep -v '\.s$' | grep -v '\.py$' | grep -v '\.hpp$' \
    | grep -v '\.S$' | grep -v '\.asm$'                   \
    | while read -r file; do
      rm -f "$file" || true
    done
  find . -type d -empty -delete
)
}

tar xzf "${GRPCIO_TAR_GZ}" -C "${GRPCIO_STRIP_TEMPDIR}"
( cd "${GRPCIO_STRIP_TEMPDIR}"
  find . -type d -name .git -exec rm -fr {} \; || true
  for dir in */third_party/*; do
    clean_non_source_files "${dir}" || true
  done
  tar czf "${GRPCIO_STRIPPED_TAR_GZ}" -- *
  chmod ugo+r "${GRPCIO_STRIPPED_TAR_GZ}"
)
mv "${GRPCIO_STRIPPED_TAR_GZ}" "${GRPCIO_TAR_GZ}"

"${PYTHON}" tools/distrib/python/make_grpcio_tools.py

${SETARCH_CMD} "${PYTHON}" tools/distrib/python/grpcio_tools/setup.py sdist

${SETARCH_CMD} "${PYTHON}" tools/distrib/python/grpcio_tools/setup.py bdist_wheel $WHEEL_PLAT_NAME_FLAG

if [ "$GRPC_BUILD_MAC" == "" ]; then
  "${PYTHON}" src/python/grpcio_observability/make_grpcio_observability.py
  ${SETARCH_CMD} "${PYTHON}" src/python/grpcio_observability/setup.py sdist

  ${SETARCH_CMD} "${PYTHON}" src/python/grpcio_observability/setup.py bdist_wheel $WHEEL_PLAT_NAME_FLAG
fi

if [ "$GRPC_SKIP_TWINE_CHECK" == "" ]
then

  "${PYTHON}" -m pip install virtualenv
  "${PYTHON}" -m virtualenv venv || { "${PYTHON}" -m pip install virtualenv==20.0.23 && "${PYTHON}" -m virtualenv venv; }

  venv/bin/python -m pip install "cryptography==40.0.0" "twine==5.0.0" "readme_renderer<40.0"
  venv/bin/python -m twine check dist/* tools/distrib/python/grpcio_tools/dist/*
  if [ "$GRPC_BUILD_MAC" == "" ]; then
    venv/bin/python -m twine check src/python/grpcio_observability/dist/*
  fi
  rm -rf venv/
fi

assert_is_universal_wheel()  {
  WHL="$1"
  TMPDIR=$(mktemp -d)
  unzip "$WHL" -d "$TMPDIR"
  SO=$(find "$TMPDIR" -name '*.so' | head -n1)
  if ! file "$SO" | grep "Mach-O universal binary with 2 architectures"; then
    echo "$WHL is not universal2. Found the following:" >/dev/stderr
    file "$SO" >/dev/stderr
    exit 1
  fi
}

fix_faulty_universal2_wheel() {
  WHL="$1"
  assert_is_universal_wheel "$WHL"
  if echo "$WHL" | grep "x86_64"; then
    UPDATED_NAME="${WHL//x86_64/universal2}"
    mv "$WHL" "$UPDATED_NAME"
  fi
}

if [ "$GRPC_BUILD_MAC" != "" ]; then
  for WHEEL in dist/*.whl tools/distrib/python/grpcio_tools/dist/*.whl; do
    fix_faulty_universal2_wheel "$WHEEL"
  done
fi

if [ "$GRPC_RUN_AUDITWHEEL_REPAIR" != "" ]
then
  for wheel in dist/*.whl; do
    "${AUDITWHEEL}" show "$wheel" | tee /dev/stderr |  grep -E -w "$AUDITWHEEL_PLAT"
    "${AUDITWHEEL}" repair "$wheel" --strip --wheel-dir "$ARTIFACT_DIR"
    rm "$wheel"
  done
  for wheel in tools/distrib/python/grpcio_tools/dist/*.whl; do
    "${AUDITWHEEL}" show "$wheel" | tee /dev/stderr |  grep -E -w "$AUDITWHEEL_PLAT"
    "${AUDITWHEEL}" repair "$wheel" --strip --wheel-dir "$ARTIFACT_DIR"
    rm "$wheel"
  done
else
  cp -r dist/*.whl "$ARTIFACT_DIR"
  cp -r tools/distrib/python/grpcio_tools/dist/*.whl "$ARTIFACT_DIR"
fi

cp -r dist/*.tar.gz "$ARTIFACT_DIR"
cp -r tools/distrib/python/grpcio_tools/dist/*.tar.gz "$ARTIFACT_DIR"

if [ "$GRPC_BUILD_MAC" == "" ]; then
  if [ "$GRPC_RUN_AUDITWHEEL_REPAIR" != "" ]
  then
    for wheel in src/python/grpcio_observability/dist/*.whl; do
      "${AUDITWHEEL}" show "$wheel" | tee /dev/stderr |  grep -E -w "$AUDITWHEEL_PLAT"
      "${AUDITWHEEL}" repair "$wheel" --strip --wheel-dir "$ARTIFACT_DIR"
      rm "$wheel"
    done
  else
    cp -r src/python/grpcio_observability/dist/*.whl "$ARTIFACT_DIR"
  fi
  cp -r src/python/grpcio_observability/dist/*.tar.gz "$ARTIFACT_DIR"

  if [ "$GRPC_BUILD_MAC" == "" ]; then
    ${SETARCH_CMD} "${PYTHON}" src/python/grpcio_csm_observability/setup.py \
        sdist bdist_wheel
    cp -r src/python/grpcio_csm_observability/dist/* "$ARTIFACT_DIR"
  fi
fi

if [ "$GRPC_BUILD_GRPCIO_TOOLS_DEPENDENTS" != "" ]
then
  "${PYTHON}" -m pip install -rrequirements.txt

  if [ "$("$PYTHON" -c "import sys; print(sys.version_info[0])")" == "2" ]
  then

    "${PYTHON}" -m pip install futures>=2.2.0 enum34>=1.0.4
  fi

  "${PYTHON}" -m pip install grpcio --no-index --find-links "file://$ARTIFACT_DIR/"
  "${PYTHON}" -m pip install grpcio-tools --no-index --find-links "file://$ARTIFACT_DIR/"

  ${SETARCH_CMD} "${PYTHON}" tools/distrib/python/xds_protos/setup.py \
      sdist bdist_wheel install
  cp -r tools/distrib/python/xds_protos/dist/* "$ARTIFACT_DIR"

  ${SETARCH_CMD} "${PYTHON}" src/python/grpcio_testing/setup.py preprocess \
      sdist bdist_wheel
  cp -r src/python/grpcio_testing/dist/* "$ARTIFACT_DIR"

  ${SETARCH_CMD} "${PYTHON}" src/python/grpcio_channelz/setup.py \
      preprocess build_package_protos sdist bdist_wheel
  cp -r src/python/grpcio_channelz/dist/* "$ARTIFACT_DIR"

  ${SETARCH_CMD} "${PYTHON}" src/python/grpcio_health_checking/setup.py \
      preprocess build_package_protos sdist bdist_wheel
  cp -r src/python/grpcio_health_checking/dist/* "$ARTIFACT_DIR"

  ${SETARCH_CMD} "${PYTHON}" src/python/grpcio_reflection/setup.py \
      preprocess build_package_protos sdist bdist_wheel
  cp -r src/python/grpcio_reflection/dist/* "$ARTIFACT_DIR"

  ${SETARCH_CMD} "${PYTHON}" src/python/grpcio_status/setup.py \
      preprocess sdist bdist_wheel
  cp -r src/python/grpcio_status/dist/* "$ARTIFACT_DIR"

  "${PYTHON}" -m pip install xds-protos --no-index --find-links "file://$ARTIFACT_DIR/"

  ${SETARCH_CMD} "${PYTHON}" src/python/grpcio_csds/setup.py \
      sdist bdist_wheel
  cp -r src/python/grpcio_csds/dist/* "$ARTIFACT_DIR"

  "${PYTHON}" -m pip install grpcio-channelz --no-index --find-links "file://$ARTIFACT_DIR/"
  "${PYTHON}" -m pip install grpcio-csds --no-index --find-links "file://$ARTIFACT_DIR/"
  ${SETARCH_CMD} "${PYTHON}" src/python/grpcio_admin/setup.py \
      sdist bdist_wheel
  cp -r src/python/grpcio_admin/dist/* "$ARTIFACT_DIR"

fi
