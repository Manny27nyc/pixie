// Code generated by MockGen. DO NOT EDIT.
// Source: service.pb.go

// Package mock_querybrokerpb is a generated GoMock package.
package mock_querybrokerpb

import (
	context "context"
	gomock "github.com/golang/mock/gomock"
	grpc "google.golang.org/grpc"
	plannerpb "pixielabs.ai/pixielabs/src/carnot/planner/plannerpb"
	querybrokerpb "pixielabs.ai/pixielabs/src/vizier/services/query_broker/querybrokerpb"
	reflect "reflect"
)

// MockQueryBrokerServiceClient is a mock of QueryBrokerServiceClient interface
type MockQueryBrokerServiceClient struct {
	ctrl     *gomock.Controller
	recorder *MockQueryBrokerServiceClientMockRecorder
}

// MockQueryBrokerServiceClientMockRecorder is the mock recorder for MockQueryBrokerServiceClient
type MockQueryBrokerServiceClientMockRecorder struct {
	mock *MockQueryBrokerServiceClient
}

// NewMockQueryBrokerServiceClient creates a new mock instance
func NewMockQueryBrokerServiceClient(ctrl *gomock.Controller) *MockQueryBrokerServiceClient {
	mock := &MockQueryBrokerServiceClient{ctrl: ctrl}
	mock.recorder = &MockQueryBrokerServiceClientMockRecorder{mock}
	return mock
}

// EXPECT returns an object that allows the caller to indicate expected use
func (m *MockQueryBrokerServiceClient) EXPECT() *MockQueryBrokerServiceClientMockRecorder {
	return m.recorder
}

// GetAgentInfo mocks base method
func (m *MockQueryBrokerServiceClient) GetAgentInfo(ctx context.Context, in *querybrokerpb.AgentInfoRequest, opts ...grpc.CallOption) (*querybrokerpb.AgentInfoResponse, error) {
	varargs := []interface{}{ctx, in}
	for _, a := range opts {
		varargs = append(varargs, a)
	}
	ret := m.ctrl.Call(m, "GetAgentInfo", varargs...)
	ret0, _ := ret[0].(*querybrokerpb.AgentInfoResponse)
	ret1, _ := ret[1].(error)
	return ret0, ret1
}

// GetAgentInfo indicates an expected call of GetAgentInfo
func (mr *MockQueryBrokerServiceClientMockRecorder) GetAgentInfo(ctx, in interface{}, opts ...interface{}) *gomock.Call {
	varargs := append([]interface{}{ctx, in}, opts...)
	return mr.mock.ctrl.RecordCallWithMethodType(mr.mock, "GetAgentInfo", reflect.TypeOf((*MockQueryBrokerServiceClient)(nil).GetAgentInfo), varargs...)
}

// ExecuteQuery mocks base method
func (m *MockQueryBrokerServiceClient) ExecuteQuery(ctx context.Context, in *plannerpb.QueryRequest, opts ...grpc.CallOption) (*querybrokerpb.VizierQueryResponse, error) {
	varargs := []interface{}{ctx, in}
	for _, a := range opts {
		varargs = append(varargs, a)
	}
	ret := m.ctrl.Call(m, "ExecuteQuery", varargs...)
	ret0, _ := ret[0].(*querybrokerpb.VizierQueryResponse)
	ret1, _ := ret[1].(error)
	return ret0, ret1
}

// ExecuteQuery indicates an expected call of ExecuteQuery
func (mr *MockQueryBrokerServiceClientMockRecorder) ExecuteQuery(ctx, in interface{}, opts ...interface{}) *gomock.Call {
	varargs := append([]interface{}{ctx, in}, opts...)
	return mr.mock.ctrl.RecordCallWithMethodType(mr.mock, "ExecuteQuery", reflect.TypeOf((*MockQueryBrokerServiceClient)(nil).ExecuteQuery), varargs...)
}

// GetSchemas mocks base method
func (m *MockQueryBrokerServiceClient) GetSchemas(ctx context.Context, in *querybrokerpb.SchemaRequest, opts ...grpc.CallOption) (*querybrokerpb.SchemaResponse, error) {
	varargs := []interface{}{ctx, in}
	for _, a := range opts {
		varargs = append(varargs, a)
	}
	ret := m.ctrl.Call(m, "GetSchemas", varargs...)
	ret0, _ := ret[0].(*querybrokerpb.SchemaResponse)
	ret1, _ := ret[1].(error)
	return ret0, ret1
}

// GetSchemas indicates an expected call of GetSchemas
func (mr *MockQueryBrokerServiceClientMockRecorder) GetSchemas(ctx, in interface{}, opts ...interface{}) *gomock.Call {
	varargs := append([]interface{}{ctx, in}, opts...)
	return mr.mock.ctrl.RecordCallWithMethodType(mr.mock, "GetSchemas", reflect.TypeOf((*MockQueryBrokerServiceClient)(nil).GetSchemas), varargs...)
}

// ReceiveAgentQueryResult mocks base method
func (m *MockQueryBrokerServiceClient) ReceiveAgentQueryResult(ctx context.Context, in *querybrokerpb.AgentQueryResultRequest, opts ...grpc.CallOption) (*querybrokerpb.AgentQueryResultResponse, error) {
	varargs := []interface{}{ctx, in}
	for _, a := range opts {
		varargs = append(varargs, a)
	}
	ret := m.ctrl.Call(m, "ReceiveAgentQueryResult", varargs...)
	ret0, _ := ret[0].(*querybrokerpb.AgentQueryResultResponse)
	ret1, _ := ret[1].(error)
	return ret0, ret1
}

// ReceiveAgentQueryResult indicates an expected call of ReceiveAgentQueryResult
func (mr *MockQueryBrokerServiceClientMockRecorder) ReceiveAgentQueryResult(ctx, in interface{}, opts ...interface{}) *gomock.Call {
	varargs := append([]interface{}{ctx, in}, opts...)
	return mr.mock.ctrl.RecordCallWithMethodType(mr.mock, "ReceiveAgentQueryResult", reflect.TypeOf((*MockQueryBrokerServiceClient)(nil).ReceiveAgentQueryResult), varargs...)
}

// MockQueryBrokerServiceServer is a mock of QueryBrokerServiceServer interface
type MockQueryBrokerServiceServer struct {
	ctrl     *gomock.Controller
	recorder *MockQueryBrokerServiceServerMockRecorder
}

// MockQueryBrokerServiceServerMockRecorder is the mock recorder for MockQueryBrokerServiceServer
type MockQueryBrokerServiceServerMockRecorder struct {
	mock *MockQueryBrokerServiceServer
}

// NewMockQueryBrokerServiceServer creates a new mock instance
func NewMockQueryBrokerServiceServer(ctrl *gomock.Controller) *MockQueryBrokerServiceServer {
	mock := &MockQueryBrokerServiceServer{ctrl: ctrl}
	mock.recorder = &MockQueryBrokerServiceServerMockRecorder{mock}
	return mock
}

// EXPECT returns an object that allows the caller to indicate expected use
func (m *MockQueryBrokerServiceServer) EXPECT() *MockQueryBrokerServiceServerMockRecorder {
	return m.recorder
}

// GetAgentInfo mocks base method
func (m *MockQueryBrokerServiceServer) GetAgentInfo(arg0 context.Context, arg1 *querybrokerpb.AgentInfoRequest) (*querybrokerpb.AgentInfoResponse, error) {
	ret := m.ctrl.Call(m, "GetAgentInfo", arg0, arg1)
	ret0, _ := ret[0].(*querybrokerpb.AgentInfoResponse)
	ret1, _ := ret[1].(error)
	return ret0, ret1
}

// GetAgentInfo indicates an expected call of GetAgentInfo
func (mr *MockQueryBrokerServiceServerMockRecorder) GetAgentInfo(arg0, arg1 interface{}) *gomock.Call {
	return mr.mock.ctrl.RecordCallWithMethodType(mr.mock, "GetAgentInfo", reflect.TypeOf((*MockQueryBrokerServiceServer)(nil).GetAgentInfo), arg0, arg1)
}

// ExecuteQuery mocks base method
func (m *MockQueryBrokerServiceServer) ExecuteQuery(arg0 context.Context, arg1 *plannerpb.QueryRequest) (*querybrokerpb.VizierQueryResponse, error) {
	ret := m.ctrl.Call(m, "ExecuteQuery", arg0, arg1)
	ret0, _ := ret[0].(*querybrokerpb.VizierQueryResponse)
	ret1, _ := ret[1].(error)
	return ret0, ret1
}

// ExecuteQuery indicates an expected call of ExecuteQuery
func (mr *MockQueryBrokerServiceServerMockRecorder) ExecuteQuery(arg0, arg1 interface{}) *gomock.Call {
	return mr.mock.ctrl.RecordCallWithMethodType(mr.mock, "ExecuteQuery", reflect.TypeOf((*MockQueryBrokerServiceServer)(nil).ExecuteQuery), arg0, arg1)
}

// GetSchemas mocks base method
func (m *MockQueryBrokerServiceServer) GetSchemas(arg0 context.Context, arg1 *querybrokerpb.SchemaRequest) (*querybrokerpb.SchemaResponse, error) {
	ret := m.ctrl.Call(m, "GetSchemas", arg0, arg1)
	ret0, _ := ret[0].(*querybrokerpb.SchemaResponse)
	ret1, _ := ret[1].(error)
	return ret0, ret1
}

// GetSchemas indicates an expected call of GetSchemas
func (mr *MockQueryBrokerServiceServerMockRecorder) GetSchemas(arg0, arg1 interface{}) *gomock.Call {
	return mr.mock.ctrl.RecordCallWithMethodType(mr.mock, "GetSchemas", reflect.TypeOf((*MockQueryBrokerServiceServer)(nil).GetSchemas), arg0, arg1)
}

// ReceiveAgentQueryResult mocks base method
func (m *MockQueryBrokerServiceServer) ReceiveAgentQueryResult(arg0 context.Context, arg1 *querybrokerpb.AgentQueryResultRequest) (*querybrokerpb.AgentQueryResultResponse, error) {
	ret := m.ctrl.Call(m, "ReceiveAgentQueryResult", arg0, arg1)
	ret0, _ := ret[0].(*querybrokerpb.AgentQueryResultResponse)
	ret1, _ := ret[1].(error)
	return ret0, ret1
}

// ReceiveAgentQueryResult indicates an expected call of ReceiveAgentQueryResult
func (mr *MockQueryBrokerServiceServerMockRecorder) ReceiveAgentQueryResult(arg0, arg1 interface{}) *gomock.Call {
	return mr.mock.ctrl.RecordCallWithMethodType(mr.mock, "ReceiveAgentQueryResult", reflect.TypeOf((*MockQueryBrokerServiceServer)(nil).ReceiveAgentQueryResult), arg0, arg1)
}
