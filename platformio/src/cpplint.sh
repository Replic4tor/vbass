#!/bin/bash
echo Running cpplint...
cpplint \
            --verbose=0 \
            --recursive \
            --exclude=vsecclib-ocpp/OCPP/ocpp_schemas_raw_strings/* \
            --exclude=vsecclib-ocpp/ThirdParty/* \
            --exclude=vsecclib-ocpp/Utils/finite_state_machine/* \
            --exclude=vsecclib-ocpp/OCPP/ocpp_schemas_cpp/* \
            --exclude=cmake*/* \
            --exclude=BaseBranch/* \
             ./* \
            1> cpplint.task \
            2> cpplint.log || true && touch cpplint.log

REPORT_LASTLINE=$(tail -n  1 cpplint.task)
PATTERN="Total errors found:"
if grep -q "$PATTERN" <<< "$REPORT_LASTLINE"; then
  echo $REPORT_LASTLINE;
else
  echo "Total errors found: 0";
fi
