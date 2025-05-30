<?php

/*
 *
 * Copyright 2015 gRPC authors.
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

namespace Grpc;

class BaseStub
{
    private $hostname;
    private $hostname_override;
    private $channel;
    private $call_invoker;

    private $update_metadata;

    public function __construct($hostname, $opts, $channel = null)
    {
        if (!method_exists('Grpc\ChannelCredentials', 'isDefaultRootsPemSet') ||
            !ChannelCredentials::isDefaultRootsPemSet()) {
            $ssl_roots = file_get_contents(
                dirname(__FILE__).'/../../../../etc/roots.pem'
            );
            ChannelCredentials::setDefaultRootsPem($ssl_roots);
        }

        $this->hostname = $hostname;
        $this->update_metadata = null;
        if (isset($opts['update_metadata'])) {
            if (is_callable($opts['update_metadata'])) {
                $this->update_metadata = $opts['update_metadata'];
            }
            unset($opts['update_metadata']);
        }
        if (!empty($opts['grpc.ssl_target_name_override'])) {
            $this->hostname_override = $opts['grpc.ssl_target_name_override'];
        }
        if (isset($opts['grpc_call_invoker'])) {
            $this->call_invoker = $opts['grpc_call_invoker'];
            unset($opts['grpc_call_invoker']);
            $channel_opts = $this->updateOpts($opts);

            $this->channel = $this->call_invoker->createChannelFactory($hostname, $channel_opts);
            return;
        }
        $this->call_invoker = new DefaultCallInvoker();
        if ($channel) {
            if (!is_a($channel, 'Grpc\Channel') &&
                !is_a($channel, 'Grpc\Internal\InterceptorChannel')) {
                throw new \Exception('The channel argument is not a Channel object '.
                    'or an InterceptorChannel object created by '.
                    'Interceptor::intercept($channel, Interceptor|Interceptor[] $interceptors)');
            }
            $this->channel = $channel;
            return;
        }

        $this->channel = static::getDefaultChannel($hostname, $opts);
    }

    private static function updateOpts($opts) {
        if (!empty($opts['grpc.primary_user_agent'])) {
            $opts['grpc.primary_user_agent'] .= ' ';
        } else {
            $opts['grpc.primary_user_agent'] = '';
        }
        if (defined('\Grpc\VERSION')) {
            $version_str = \Grpc\VERSION;
        } else {
            if (!file_exists($composerFile = __DIR__.'/../../composer.json')) {

                $composerFile = __DIR__.'/../composer.json';
            }
            $package_config = json_decode(file_get_contents($composerFile), true);
            $version_str = $package_config['version'];
        }
        $opts['grpc.primary_user_agent'] .= 'grpc-php/'.$version_str;
        if (!array_key_exists('credentials', $opts)) {
            throw new \Exception("The opts['credentials'] key is now ".
                'required. Please see one of the '.
                'ChannelCredentials::create methods');
        }
        return $opts;
    }

    public static function getDefaultChannel($hostname, array $opts)
    {
        $channel_opts = self::updateOpts($opts);
        return new Channel($hostname, $channel_opts);
    }

    public function getTarget()
    {
        return $this->channel->getTarget();
    }

    public function getConnectivityState($try_to_connect = false)
    {
        return $this->channel->getConnectivityState($try_to_connect);
    }

    public function waitForReady($timeout)
    {
        $new_state = $this->getConnectivityState(true);
        if ($this->_checkConnectivityState($new_state)) {
            return true;
        }

        $now = Timeval::now();
        $delta = new Timeval($timeout);
        $deadline = $now->add($delta);

        while ($this->channel->watchConnectivityState($new_state, $deadline)) {

            $new_state = $this->getConnectivityState();
            if ($this->_checkConnectivityState($new_state)) {
                return true;
            }
        }

        $new_state = $this->getConnectivityState();

        return $this->_checkConnectivityState($new_state);
    }

    public function close()
    {
        $this->channel->close();
    }

    private function _checkConnectivityState($new_state)
    {
        if ($new_state == \Grpc\CHANNEL_READY) {
            return true;
        }
        if ($new_state == \Grpc\CHANNEL_FATAL_FAILURE) {
            throw new \Exception('Failed to connect to server');
        }

        return false;
    }

    private function _get_jwt_aud_uri($method)
    {

        $last_slash_idx = strrpos($method, '/');
        if ($last_slash_idx === false) {
            throw new \InvalidArgumentException(
                'service name must have a slash'
            );
        }
        $service_name = substr($method, 0, $last_slash_idx);

        if ($this->hostname_override) {
            $hostname = $this->hostname_override;
        } else {
            $hostname = $this->hostname;
        }

        if ((strlen($hostname) > 4) && (substr($hostname, -4) === ":443")) {
            $hostname = substr($hostname, 0, -4);
        }

        return 'https://'.$hostname.$service_name;
    }

    private function _validate_and_normalize_metadata($metadata)
    {
        $metadata_copy = [];
        foreach ($metadata as $key => $value) {
            if (!preg_match('/^[.A-Za-z\d_-]+$/', $key)) {
                throw new \InvalidArgumentException(
                    'Metadata keys must be nonempty strings containing only '.
                    'alphanumeric characters, hyphens, underscores and dots'
                );
            }
            $metadata_copy[strtolower($key)] = $value;
        }

        return $metadata_copy;
    }

    private function _GrpcUnaryUnary($channel)
    {
        return function ($method,
                         $argument,
                         $deserialize,
                         array $metadata = [],
                         array $options = []) use ($channel) {
            $call = $this->call_invoker->UnaryCall(
                $channel,
                $method,
                $deserialize,
                $options
            );
            $jwt_aud_uri = $this->_get_jwt_aud_uri($method);
            if (is_callable($this->update_metadata)) {
                $metadata = call_user_func(
                    $this->update_metadata,
                    $metadata,
                    $jwt_aud_uri
                );
            }
            $metadata = $this->_validate_and_normalize_metadata(
                $metadata
            );
            $call->start($argument, $metadata, $options);
            return $call;
        };
    }

    private function _GrpcStreamUnary($channel)
    {
        return function ($method,
                         $deserialize,
                         array $metadata = [],
                         array $options = []) use ($channel) {
            $call = $this->call_invoker->ClientStreamingCall(
                $channel,
                $method,
                $deserialize,
                $options
            );
            $jwt_aud_uri = $this->_get_jwt_aud_uri($method);
            if (is_callable($this->update_metadata)) {
                $metadata = call_user_func(
                    $this->update_metadata,
                    $metadata,
                    $jwt_aud_uri
                );
            }
            $metadata = $this->_validate_and_normalize_metadata(
                $metadata
            );
            $call->start($metadata);
            return $call;
        };
    }

    private function _GrpcUnaryStream($channel)
    {
        return function ($method,
                         $argument,
                         $deserialize,
                         array $metadata = [],
                         array $options = []) use ($channel) {
            $call = $this->call_invoker->ServerStreamingCall(
                $channel,
                $method,
                $deserialize,
                $options
            );
            $jwt_aud_uri = $this->_get_jwt_aud_uri($method);
            if (is_callable($this->update_metadata)) {
                $metadata = call_user_func(
                    $this->update_metadata,
                    $metadata,
                    $jwt_aud_uri
                );
            }
            $metadata = $this->_validate_and_normalize_metadata(
                $metadata
            );
            $call->start($argument, $metadata, $options);
            return $call;
        };
    }

    private function _GrpcStreamStream($channel)
    {
        return function ($method,
                         $deserialize,
                         array $metadata = [],
                         array $options = []) use ($channel) {
            $call = $this->call_invoker->BidiStreamingCall(
                $channel,
                $method,
                $deserialize,
                $options
            );
            $jwt_aud_uri = $this->_get_jwt_aud_uri($method);
            if (is_callable($this->update_metadata)) {
                $metadata = call_user_func(
                    $this->update_metadata,
                    $metadata,
                    $jwt_aud_uri
                );
            }
            $metadata = $this->_validate_and_normalize_metadata(
                $metadata
            );
            $call->start($metadata);

            return $call;
        };
    }

    private function _UnaryUnaryCallFactory($channel)
    {
        if (is_a($channel, 'Grpc\Internal\InterceptorChannel')) {
            return function ($method,
                             $argument,
                             $deserialize,
                             array $metadata = [],
                             array $options = []) use ($channel) {
                return $channel->getInterceptor()->interceptUnaryUnary(
                    $method,
                    $argument,
                    $deserialize,
                    $this->_UnaryUnaryCallFactory($channel->getNext()),
                    $metadata,
                    $options
                );
            };
        }
        return $this->_GrpcUnaryUnary($channel);
    }

    private function _UnaryStreamCallFactory($channel)
    {
        if (is_a($channel, 'Grpc\Internal\InterceptorChannel')) {
            return function ($method,
                             $argument,
                             $deserialize,
                             array $metadata = [],
                             array $options = []) use ($channel) {
                return $channel->getInterceptor()->interceptUnaryStream(
                    $method,
                    $argument,
                    $deserialize,
                    $this->_UnaryStreamCallFactory($channel->getNext()),
                    $metadata,
                    $options
                );
            };
        }
        return $this->_GrpcUnaryStream($channel);
    }

    private function _StreamUnaryCallFactory($channel)
    {
        if (is_a($channel, 'Grpc\Internal\InterceptorChannel')) {
            return function ($method,
                             $deserialize,
                             array $metadata = [],
                             array $options = []) use ($channel) {
                return $channel->getInterceptor()->interceptStreamUnary(
                    $method,
                    $deserialize,
                    $this->_StreamUnaryCallFactory($channel->getNext()),
                    $metadata,
                    $options
                );
            };
        }
        return $this->_GrpcStreamUnary($channel);
    }

    private function _StreamStreamCallFactory($channel)
    {
        if (is_a($channel, 'Grpc\Internal\InterceptorChannel')) {
            return function ($method,
                             $deserialize,
                             array $metadata = [],
                             array $options = []) use ($channel) {
                return $channel->getInterceptor()->interceptStreamStream(
                    $method,
                    $deserialize,
                    $this->_StreamStreamCallFactory($channel->getNext()),
                    $metadata,
                    $options
                );
            };
        }
        return $this->_GrpcStreamStream($channel);
    }

    protected function _simpleRequest(
        $method,
        $argument,
        $deserialize,
        array $metadata = [],
        array $options = []
    ) {
        $call_factory = $this->_UnaryUnaryCallFactory($this->channel);
        $call = $call_factory($method, $argument, $deserialize, $metadata, $options);
        return $call;
    }

    protected function _clientStreamRequest(
        $method,
        $deserialize,
        array $metadata = [],
        array $options = []
    ) {
        $call_factory = $this->_StreamUnaryCallFactory($this->channel);
        $call = $call_factory($method, $deserialize, $metadata, $options);
        return $call;
    }

    protected function _serverStreamRequest(
        $method,
        $argument,
        $deserialize,
        array $metadata = [],
        array $options = []
    ) {
        $call_factory = $this->_UnaryStreamCallFactory($this->channel);
        $call = $call_factory($method, $argument, $deserialize, $metadata, $options);
        return $call;
    }

    protected function _bidiRequest(
        $method,
        $deserialize,
        array $metadata = [],
        array $options = []
    ) {
        $call_factory = $this->_StreamStreamCallFactory($this->channel);
        $call = $call_factory($method, $deserialize, $metadata, $options);
        return $call;
    }
}
