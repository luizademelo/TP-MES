<?php

/*
 *
 * Copyright 2017 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

require dirname(__FILE__).'/vendor/autoload.php';
require dirname(__FILE__).'/histogram.php';

function hardAssert($value, $error_message)
{
    if (!$value) {
        echo $error_message."\n";
        exit(1);
    }
}

function hardAssertIfStatusOk($status)
{
    if ($status->code !== Grpc\STATUS_OK) {
        echo "Call did not complete successfully. Status object:\n";
        var_dump($status);
        exit(1);
    }
}

function qps_client_main($proxy_address, $server_ind) {
    echo "[php-client] Initiating php client\n";

    $proxystubopts = [];
    $proxystubopts['credentials'] = Grpc\ChannelCredentials::createInsecure();
    $proxystub = new Grpc\Testing\ProxyClientServiceClient($proxy_address, $proxystubopts);
    list($config, $status) = $proxystub->GetConfig(new Grpc\Testing\PBVoid())->wait();
    hardAssertIfStatusOk($status);
    hardAssert($config->getOutstandingRpcsPerChannel() == 1, "Only 1 outstanding RPC supported");

    echo "[php-client] Got configuration from proxy, target is '$server_ind'th server" . $config->getServerTargets()[$server_ind] . "\n";
    $histres = $config->getHistogramParams()->getResolution();
    $histmax = $config->getHistogramParams()->getMaxPossible();

    $stubopts = [];
    if ($config->getSecurityParams()) {
        if ($config->getSecurityParams()->getUseTestCa()) {
            $stubopts['credentials'] = Grpc\ChannelCredentials::createSsl(
                file_get_contents(dirname(__FILE__).'/../data/ca.pem'));
        } else {
            $stubopts['credentials'] = Grpc\ChannelCredentials::createSsl(null);
        }
        $override = $config->getSecurityParams()->getServerHostOverride();
        if ($override) {
            $stubopts['grpc.ssl_target_name_override'] = $override;
            $stubopts['grpc.default_authority'] = $override;
        }
    } else {
        $stubopts['credentials'] = Grpc\ChannelCredentials::createInsecure();
    }
    echo "[php-client] Initiating php benchmarking client\n";

    $stub = new Grpc\Testing\BenchmarkServiceClient(
        $config->getServerTargets()[$server_ind], $stubopts);
    $req = new Grpc\Testing\SimpleRequest();

    $req->setResponseType(Grpc\Testing\PayloadType::COMPRESSABLE);
    $req->setResponseSize($config->getPayloadConfig()->getSimpleParams()->getRespSize());
    $payload = new Grpc\Testing\Payload();
    $payload->setType(Grpc\Testing\PayloadType::COMPRESSABLE);
    $payload->setBody(str_repeat("\0", $config->getPayloadConfig()->getSimpleParams()->getReqSize()));
    $req->setPayload($payload);

    if (0 && $config->getLoadParams()->getLoad() == "poisson") {
        $poisson = true;
        $lamrecip = 1.0/($config->getLoadParams()->getPoisson()->getOfferedLoad());
        $issue = microtime(true) + $lamrecip * -log(1.0-rand()/(getrandmax()+1));
    } else {
        $poisson = false;
    }
    $histogram = new Histogram($histres, $histmax);
    $histogram->clean();
    $count = 0;
    $histogram_result = new Grpc\Testing\HistogramData;
    $telehist = $proxystub->ReportHist();
    if ($config->getRpcType() == Grpc\Testing\RpcType::UNARY) {
        while (1) {
            if ($poisson) {
                time_sleep_until($issue);
                $issue = $issue + $lamrecip * -log(1.0-rand()/(getrandmax()+1));
            }
            $startreq = microtime(true);
            list($resp,$status) = $stub->UnaryCall($req)->wait();
            hardAssertIfStatusOk($status);
            $histogram->add((microtime(true)-$startreq)*1e9);
            $count += 1;
            if ($count == 2000) {
              $contents = $histogram->contents();
              $histogram_result->setBucket($contents);
              $histogram_result->setMinSeen($histogram->minimum());
              $histogram_result->setMaxSeen($histogram->maximum());
              $histogram_result->setSum($histogram->sum());
              $histogram_result->setSumOfSquares($histogram->sum_of_squares());
              $histogram_result->setCount($histogram->count());
              $telehist->write($histogram_result);
              $histogram->clean();
              $count = 0;
            }
        }
    } else {
        $stream = $stub->StreamingCall();
        while (1) {
            if ($poisson) {
                time_sleep_until($issue);
                $issue = $issue + $lamrecip * -log(1.0-rand()/(getrandmax()+1));
            }
            $startreq = microtime(true);
            $stream->write($req);
            $resp = $stream->read();
            $histogram->add((microtime(true)-$startreq)*1e9);
            $count += 1;
            if ($count == 2000) {
              $contents = $histogram->contents();
              $histogram_result->setBucket($contents);
              $histogram_result->setMinSeen($histogram->minimum());
              $histogram_result->setMaxSeen($histogram->maximum());
              $histogram_result->setSum($histogram->sum());
              $histogram_result->setSumOfSquares($histogram->sum_of_squares());
              $histogram_result->setCount($histogram->count());
              $telehist->write($histogram_result);
              $histogram->clean();
              $count = 0;
          }
        }
    }
}

ini_set('display_startup_errors', 1);
ini_set('display_errors', 1);
error_reporting(-1);
qps_client_main($argv[1], $argv[2]);
