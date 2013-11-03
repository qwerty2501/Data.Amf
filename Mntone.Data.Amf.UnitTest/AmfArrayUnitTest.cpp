#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;
namespace WG = Windows::Globalization;


TEST_CLASS(AmfArrayUnitTest){


	TEST_METHOD(ConstractorTest)
	{
		auto amfArray = ref new AmfArray();
		Assert::IsTrue(amfArray->ValueType == AmfValueType::Array);
		Assert::IsTrue(amfArray->Size == 0);
	}


	TEST_METHOD(CreateStrictArrayTest_Member)
	{
		auto strictArray = AmfArray::CreateStrictArray();
		
		Assert::IsTrue(strictArray->ValueType == AmfValueType::Array);
		Assert::IsTrue(strictArray->Size == 0);
	}


	TEST_METHOD(AppendAndGetFirstTest)
	{
		auto amfArray = ref new AmfArray();
		amfArray->Append(AmfValue::CreateBooleanValue(false));
		
		Assert::IsTrue(amfArray->Size == 1);
		
		auto firstValue = amfArray->GetAt(0);

		Assert::IsTrue(firstValue->ValueType == AmfValueType::Boolean);

		Assert::IsFalse(firstValue->GetBoolean());

	}

	TEST_METHOD(NoneItemTest_OutOfRangeException)
	{
		auto amfArray = ref new AmfArray();

		Assert::ExpectException<Platform::OutOfBoundsException^>([amfArray]{
			amfArray->GetAt(0);
		});
		
	}


	TEST_METHOD(GetBooleanTest_FailureException)
	{

		failureExceptionTest([](AmfArray^ amfArray){
			amfArray->GetBoolean();
		});

	}

	TEST_METHOD(GetDoubleTest_FailureException)
	{
		failureExceptionTest([](AmfArray^ amfArray){
			amfArray->GetDouble();
		});
	}

	TEST_METHOD(GetIntegerTest_FailureException)
	{
		failureExceptionTest([](AmfArray^ amfArray){
			amfArray->GetInteger();
		});
	}


	TEST_METHOD(GetStringTest_FailureException)
	{

		failureExceptionTest([](AmfArray^ amfArray){
			amfArray->GetString();
		});
	}


	TEST_METHOD(GetDateTest_FailureException)
	{
		failureExceptionTest([](AmfArray^ amfArray){
			amfArray->GetDate();
		});
	}

	TEST_METHOD(GetByteArrayTest_FailureException)
	{
		failureExceptionTest([](AmfArray^ amfArray){
			amfArray->GetByteArray();
		});
	}

	TEST_METHOD(GetVectorIntTest_FailureException)
	{
		failureExceptionTest([](AmfArray^ amfArray){
			amfArray->GetVectorInt();
		});
	}

	TEST_METHOD(GetVectorUintTest_FailureException)
	{
		failureExceptionTest([](AmfArray^ amfArray){
			amfArray->GetVectorUint();
		});
	}


	TEST_METHOD(GetVectorDouble_FailureException)
	{
		failureExceptionTest([](AmfArray^ amfArray){
			amfArray->GetDouble();
		});
	}

	TEST_METHOD(ToStringTest_SomeItems)
	{
		auto amfArray = ref new AmfArray();

		amfArray->Append(AmfValue::CreateBooleanValue(true));
		amfArray->Append(AmfValue::CreateIntegerValue(50));

		Assert::AreEqual(L"[true, 50, ]", amfArray->ToString());
	}


	TEST_METHOD(ToStringTest_NoneItem)
	{
		auto amfArray = ref new AmfArray();

		Assert::AreEqual(L"[]", amfArray->ToString());
	}


private:

	void failureExceptionTest(std::function<void(AmfArray^)> testHandler){

		auto amfArray = ref new AmfArray();

		Assert::ExpectException<Platform::FailureException^>([amfArray, testHandler]{

			testHandler(amfArray);

		});
	}
};