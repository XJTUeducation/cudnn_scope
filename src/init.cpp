#include "scope/init/init.hpp"
#include "scope/init/flags.hpp"
#include "scope/utils/utils.hpp"
#include "scope/utils/version.hpp"

#include <cudnn.h>

#include "config.hpp"
#include "init/init.hpp"

cudnnHandle_t cudnn_handle;

void cudnn_before_init() {
  // Create a version string and tell scope about it
  // These values are defined in cudnn_scope/config.hpp.in
  RegisterVersionString(
      version(SCOPE_PROJECT_NAME, SCOPE_VERSION, SCOPE_GIT_REFSPEC, SCOPE_GIT_HASH, SCOPE_GIT_LOCAL_CHANGES));
}

int cudnn_init() {
  return PRINT_IF_ERROR(cudnnCreate(&cudnn_handle));
}

SCOPE_REGISTER_BEFORE_INIT(cudnn_before_init);
SCOPE_REGISTER_INIT(cudnn_init);