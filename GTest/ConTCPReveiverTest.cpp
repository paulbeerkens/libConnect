//
// Created by pbeerken on 8/24/17.
//

#include <gtest/gtest.h>
#include "ConSocketMock.h"
#include "../ConTCPReceiver.h"
#include <cstring>

class MockConnectionCallback : public IConnectionCallback
{
public:
    MOCK_METHOD0 (onConnected, void());

    MOCK_METHOD0 (onDisconnected, void());

    MOCK_METHOD2 (onMsg, void(void * buf, int
            len));
};


//Custom action to populate a buffer pointed to by a parameter with a specific value
ACTION_TEMPLATE(SetArgNPointeeTo, HAS_1_TEMPLATE_PARAMS(unsigned, uIndex), AND_2_VALUE_PARAMS(pData, uiDataSize))
{
    std::memcpy(std::get<uIndex>(args), pData, uiDataSize);
}

bool ONMSG_HAS_BEEN_CALLED = false;

//custom matcher to check size and content of buffer
MATCHER_P2(HasBytes, bytes, size, "")
{
    ONMSG_HAS_BEEN_CALLED = true;
    return std::get<1>(arg) == size && memcmp(std::get<0>(arg), bytes, size) == 0;
}

TEST(MyConTCPReceiverTest, ConnectReceivedString)
{
    /*  ONMSG_HAS_BEEN_CALLED = false;

      MockConnectionCallback cb;
      ConSocketMock socket;
      char rcvBuffer[] = "Hello World, test completed";
      size_t bufferSize = strlen(rcvBuffer);

      ON_CALL(socket, connect(testing::_, testing::_)).WillByDefault(testing::Return(true));
      ON_CALL(socket, createSocket()).WillByDefault(testing::Return(true));

      //Expect to only be connected once
      EXPECT_CALL(cb, onConnected()).Times(testing::Exactly(1));
      //Expect to only request to connect once
      EXPECT_CALL(socket, connect(::testing::_, ::testing::_)).Times(testing::Exactly(1));

      EXPECT_CALL(socket, createSocket()).Times(testing::AtLeast(1));
      EXPECT_CALL(socket, isSocketSet()).Times(testing::AtLeast(2));

      //send length or string using cusom SetArgNPointeeTo function
      EXPECT_CALL(socket, read(::testing::_, ::testing::_)).WillRepeatedly(
              testing::DoAll(SetArgNPointeeTo<0>(std::begin(rcvBuffer), bufferSize), testing::Return(strlen(rcvBuffer))));
      EXPECT_CALL(socket, read(::testing::_, 4)).WillRepeatedly(
              testing::DoAll(SetArgNPointeeTo<0>(&bufferSize, sizeof(bufferSize)), testing::Return(4)));

      //check that the onMsg call has the correct string using custom matcher HasBytes
      //testing::Args<0,1> is not required because this is the default
      EXPECT_CALL(cb, onMsg(::testing::_, ::testing::_)).With(testing::Args<0, 1>(HasBytes(rcvBuffer, bufferSize))).Times(
              testing::AtLeast(1));


      std::unique_ptr <ConSocket> s=std::make_unique <ConSocketImpl> ();
      ConThread<ConTCPReceiver> connection("127.0.0.1", 9877, &cb, std::move (s));
      //ConTCPReceiver connection("127.0.0.1", 9877, &cb, std::move (s));

      while (!ONMSG_HAS_BEEN_CALLED)
      {
          std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }
      connection.requestToTerminate();

      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  */
}


TEST(MyConTCPReceiverTest, ConnectReceivedStringInTwo)
{
/*    ONMSG_HAS_BEEN_CALLED = false;

    MockConnectionCallback cb;
    ConSocketMock socket;
    char rcvBuffer[] = "Hello World, test completed";
    size_t bufferSize = strlen(rcvBuffer);

    char rcvBufferA[] = "Hello World";
    size_t bufferSizeA = strlen(rcvBuffer);

    char rcvBufferB[] = ", test completed";
    size_t bufferSizeB = strlen(rcvBuffer);

    ON_CALL(socket, connect(testing::_, testing::_)).WillByDefault(testing::Return(true));
    ON_CALL(socket, createSocket()).WillByDefault(testing::Return(true));

    //Expect to only be connected once
    EXPECT_CALL(cb, onConnected()).Times(testing::Exactly(1));
    //Expect to only request to connect once
    EXPECT_CALL(socket, connect(::testing::_, ::testing::_)).Times(testing::Exactly(1));

    EXPECT_CALL(socket, createSocket()).Times(testing::AtLeast(1));
    EXPECT_CALL(socket, isSocketSet()).Times(testing::AtLeast(2));

    //send length or string using cusom SetArgNPointeeTo function
    //first time send in two times
    EXPECT_CALL(socket, read(::testing::_, ::testing::_))
            .WillOnce(testing::DoAll(SetArgNPointeeTo<0>(std::begin(rcvBufferA), bufferSizeA),
                                     testing::Return(strlen(rcvBufferA))))
            .WillOnce(testing::DoAll(SetArgNPointeeTo<0>(std::begin(rcvBufferB), bufferSizeB),
                                     testing::Return(strlen(rcvBufferB))))
            .WillRepeatedly(testing::DoAll(SetArgNPointeeTo<0>(std::begin(rcvBuffer), bufferSize),
                                           testing::Return(strlen(rcvBuffer))));


    EXPECT_CALL(socket, read(::testing::_, 4))
            .WillRepeatedly(testing::DoAll(SetArgNPointeeTo<0>(&bufferSize, sizeof(bufferSize)), testing::Return(4)));

    //check that the onMsg call has the correct string using custom matcher HasBytes
    //testing::Args<0,1> is not required because this is the default
    EXPECT_CALL(cb, onMsg(::testing::_, ::testing::_)).With(testing::Args<0, 1>(HasBytes(rcvBuffer, bufferSize))).Times(
            testing::AtLeast(1));


    ConThread<ConTCPReceiver> connection("127.0.0.1", 9877, &cb, &socket);

    while (!ONMSG_HAS_BEEN_CALLED)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    connection.requestToTerminate();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
*/
}