﻿#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;
namespace WG = Windows::Globalization;

using TestByteArray = Platform::Array<uint8>;

TEST_CLASS( Amf0UnitTest )
{
public:
	TEST_METHOD( NumberTest_0_0 )
	{
		
		TestAmf0( ref new TestByteArray{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Double );
			Assert::AreEqual( 0.0, amfValue->GetDouble() );
		} );
	}

	TEST_METHOD( NumbetTest_0_5 )
	{
		TestAmf0( ref new TestByteArray{ 0, 0x3f, 0xe0, 0, 0, 0, 0, 0, 0 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Double );
			Assert::AreEqual( 0.5, amfValue->GetDouble() );
		} );
	}

	TEST_METHOD( BooleanTest_True )
	{
		TestAmf0( ref new TestByteArray{ 1, 1 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Boolean );
			Assert::IsTrue( amfValue->GetBoolean() );
		} );
	}

	TEST_METHOD( BooleanTest_False )
	{
		TestAmf0( ref new TestByteArray{ 1, 0 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Boolean );
			Assert::IsFalse( amfValue->GetBoolean() );
		} );
	}

	TEST_METHOD( StringTest_Null )
	{
		TestAmf0( ref new TestByteArray{ 2, 0, 0 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::String );
			Assert::AreEqual( amfValue->GetString()->Data(), L"" );
		} );
	}

	TEST_METHOD( StringTest_Ascii )
	{
		TestAmf0( ref new TestByteArray{ 2, 0, 5, 0x41, 0x53, 0x43, 0x49, 0x49 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::String );
			Assert::AreEqual( amfValue->GetString()->Data(), L"ASCII" );
		} );
	}

	TEST_METHOD( StringTest_RandomCharactors1 )
	{
		TestAmf0( ref new TestByteArray{ 2, 0, 6, 0xc2, 0xbd, 0x3a, 0x20, 0x32, 0x42 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::String );
			Assert::AreEqual( L"½: 2B", amfValue->GetString()->Data() );
		} );
	}

	TEST_METHOD( StringTest_RandomCharactors2 )
	{
		TestAmf0( ref new TestByteArray{ 2, 0, 7, 0xe2, 0x91, 0xb4, 0x3a, 0x20, 0x33, 0x42 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::String );
			Assert::AreEqual( L"⑴: 3B", amfValue->GetString()->Data() );
		} );
	}

	TEST_METHOD( ObjectTest_Null )
	{
		TestAmf0( ref new TestByteArray{ 3, 0, 0, 9 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Object );
			Assert::AreEqual<uint32>( 0, amfValue->GetObject()->Size );
		} );
	}

	TEST_METHOD( ObjectTest_BStringNull )
	{
		TestAmf0( ref new TestByteArray{ 3, 0, 1, 0x42, 2, 0, 0, 0, 0, 9 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Object );

			const auto& obj = amfValue->GetObject();
			Assert::AreEqual<uint32>( 1, obj->Size );
			Assert::AreEqual( L"", obj->GetNamedString( "B" )->Data() );
		} );
	}

	TEST_METHOD( ObjectTest_More )
	{
		TestAmf0( ref new TestByteArray{ 3, 0, 1, 0x44, 2, 0, 0, 0, 1, 0x43, 2, 0, 0, 0, 0, 9 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Object );

			const auto& obj = amfValue->GetObject();
			Assert::AreEqual<uint32>( 2, obj->Size );
			Assert::IsNull( obj->GetNamedString( "D" ) );
			Assert::IsNull( obj->GetNamedString( "C" ) );
		} );
	}

	TEST_METHOD( ValueTypeTest_Null )
	{
		TestAmf0( ref new TestByteArray{ 5 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Null );
		} );
	}

	TEST_METHOD( ValueTypeTest_Undefined )
	{
		TestAmf0( ref new TestByteArray{ 6 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Undefined );
		} );
	}

	TEST_METHOD( EcmaArrayTest_Null )
	{
		TestAmf0( ref new TestByteArray{ 8, 0, 0, 0, 0, 0, 0, 9 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Array );
			Assert::AreEqual<uint32>( 0, amfValue->GetArray()->Size );
		} );
	}

	TEST_METHOD( EcmaArrayTest_String_Null )
	{
		TestAmf0( ref new TestByteArray{ 8, 0, 0, 0, 1, 0, 1, 0x30, 2, 0, 0, 0, 0, 9 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Array );
			Assert::AreEqual<uint32>( amfValue->GetArray()->Size, 1 );
			Assert::AreEqual( L"", amfValue->GetArray()->GetStringAt( 0 )->Data() );
		} );
	}

	TEST_METHOD( StrictArrayTest_Null )
	{
		TestAmf0( ref new TestByteArray{ 10, 0, 0, 0, 0 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Array );
			Assert::AreEqual<uint32>( 0, amfValue->GetArray()->Size );
		} );
	}

	TEST_METHOD( StrinctArray_0_True )
	{
		TestAmf0( ref new TestByteArray{ 10, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Array );

			const auto& ary = amfValue->GetArray();
			Assert::AreEqual<uint32>( 2, ary->Size );
			Assert::AreEqual( 0.0, ary->GetDoubleAt( 0 ) );
			Assert::IsTrue( ary->GetBooleanAt( 1 ) );
		} );
	}

	TEST_METHOD( DateTest_2013_10_13 )
	{
		TestAmf0( ref new TestByteArray{ 11, 0x42, 0x74, 0x1a, 0xd2, 0xe6, 0x18, 0x00, 0x00, 0, 0 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Date );

			const auto& dateFormat = ref new WG::DateTimeFormatting::DateTimeFormatter(
				WG::DateTimeFormatting::YearFormat::Full,
				WG::DateTimeFormatting::MonthFormat::Numeric,
				WG::DateTimeFormatting::DayFormat::Default,
				WG::DateTimeFormatting::DayOfWeekFormat::None );

			Assert::AreEqual( L"‎2013‎年‎10‎月‎13‎日", dateFormat->Format( amfValue->GetDate( ) )->Data( ) );
		} );
	}

	TEST_METHOD( DateTest_2013_11_02_20_28_52_0100 )
	{
		TestAmf0( ref new TestByteArray{ 0x0b, 0x42, 0x74, 0x21, 0x89, 0x2a, 0x18, 0x40, 0, 0xfd, 0xe4 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Date );

			const auto& dateFormat = ref new WG::DateTimeFormatting::DateTimeFormatter(
				WG::DateTimeFormatting::YearFormat::Full,
				WG::DateTimeFormatting::MonthFormat::Numeric,
				WG::DateTimeFormatting::DayFormat::Default,
				WG::DateTimeFormatting::DayOfWeekFormat::None,
				WG::DateTimeFormatting::HourFormat::Default,
				WG::DateTimeFormatting::MinuteFormat::Default,
				WG::DateTimeFormatting::SecondFormat::Default,
				ref new Platform::Collections::Vector<Platform::String^>( { "ja" } ) );

			Assert::AreEqual(L"‎2013‎年‎11‎月‎2‎日‎ ‎20‎:‎28‎:‎52", dateFormat->Format(amfValue->GetDate())->Data());
		} );
	}

	TEST_METHOD( LongStringTest )
	{
		auto ls = ref new TestByteArray( 5 + 0x10000 );
		ls[0] = 12; ls[1] = 0; ls[2] = 1; ls[3] = 0; ls[4] = 0;
		std::wstring testLs;
		for( auto i = 0; i < 0x4000; ++i )
		{
			ls[5 + 4 * i] = 0x71; ls[5 + 4 * i + 1] = 0x72; ls[5 + 4 * i + 2] = 0x73; ls[5 + 4 * i + 3] = 0x74;
			testLs += L"qrst";
		}

		TestAmf0( ls, [testLs]( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::String );
			Assert::AreEqual( testLs.c_str(), amfValue->GetString()->Data() );
		} );
	}

	TEST_METHOD( XmlDocumentTest_RootNode )
	{
		TestAmf0( ref new TestByteArray{ 0x0f, 0, 0, 0, 6, 0x3c, 0x72, 0x6f, 0x6f, 0x74, 0x3e }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Xml );
			Assert::AreEqual( L"<root>", amfValue->GetString()->Data() );
		} );
	}

	TEST_METHOD( TypedObjectTest_Null )
	{
		TestAmf0( ref new TestByteArray{ 0x10, 0, 4, 0x54, 0x65, 0x73, 0x74, 0, 0, 9 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Object );
			Assert::AreEqual<uint32>( 0, amfValue->GetObject()->Size );
			Assert::AreEqual( L"Test", amfValue->GetObject()->ClassName->Data() );
		} );
	}


	TEST_METHOD( FromValueParseTest_Double0 )
	{
		ParseTestDouble0( ValueParse );
	}

	TEST_METHOD( FromValueParseTest_ObjectNull )
	{
		ParseTestObjectNull( ValueParse );
	}

	TEST_METHOD( FromValueParseTest_ArrayNull )
	{
		ParseTestArrayNull( ValueParse );
	}

	TEST_METHOD( FromObjectParseTest_Double0 )
	{
		ParseTestDouble0( ObjectParse );
	}

	TEST_METHOD( FromObjectParseTest_ObjectNull )
	{
		ParseTestObjectNull( ObjectParse );
	}

	TEST_METHOD( FromObjectParseTest_ArrayNull )
	{
		ParseTestArrayNull( ObjectParse );
	}

	TEST_METHOD( FromArrayParseTest_Double0 )
	{
		ParseTestDouble0( ArrayParse );
	}

	TEST_METHOD( FromArrayParseTest_ObjectNull )
	{
		ParseTestObjectNull( ArrayParse );
	}

	TEST_METHOD( FromArrayParseTest_ArrayNull )
	{
		ParseTestArrayNull( ArrayParse );
	}

	TEST_METHOD( FromValueTryParseTest_Double0 )
	{
		ParseTestDouble0( ValueTryParse );
	}

	TEST_METHOD( FromValueTryParseTest_ObjectNull )
	{
		ParseTestObjectNull( ValueTryParse );
	}

	TEST_METHOD( FromValueTryParseTest_ArrayNull )
	{
		ParseTestArrayNull( ValueTryParse );
	}

	TEST_METHOD( FromObjectTryParseTest_Double0 )
	{
		ParseTestDouble0( ObjectTryParse );
	}

	TEST_METHOD( FromObjectTryParseTest_ObjectNull )
	{
		ParseTestObjectNull( ObjectTryParse );
	}

	TEST_METHOD( FromObjectTryParseTest_ArrayNull )
	{
		ParseTestArrayNull( ObjectTryParse );
	}

	TEST_METHOD( FromArrayTryParseTest_Double0 )
	{
		ParseTestDouble0( ArrayTryParse );
	}

	TEST_METHOD( FromArrayTryParseTest_ObjectNull )
	{
		ParseTestObjectNull( ArrayTryParse );
	}

	TEST_METHOD( FromArrayTryParseTest_ArrayNull )
	{
		ParseTestArrayNull( ArrayTryParse );
	}


	TEST_METHOD( MasterTest_RtmpCommandData )
	{
		TestAmf0( ref new TestByteArray{ 10, 0, 0, 0, 4, 0x02, 0x00, 0x07, 0x5f, 0x72, 0x65, 0x73, 0x75, 0x6c, 0x74, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x06, 0x66, 0x6d, 0x73, 0x56, 0x65, 0x72, 0x02, 0x00, 0x0d, 0x46, 0x4d, 0x53, 0x2f, 0x33, 0x2c, 0x30, 0x2c, 0x31, 0x2c, 0x31, 0x32, 0x33, 0x00, 0x0c, 0x63, 0x61, 0x70, 0x61, 0x62, 0x69, 0x6c, 0x69, 0x74, 0x69, 0x65, 0x73, 0x00, 0x40, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x03, 0x00, 0x05, 0x6c, 0x65, 0x76, 0x65, 0x6c, 0x02, 0x00, 0x06, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73, 0x00, 0x04, 0x63, 0x6f, 0x64, 0x65, 0x02, 0x00, 0x1d, 0x4e, 0x65, 0x74, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x2e, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x2e, 0x53, 0x75, 0x63, 0x63, 0x65, 0x73, 0x73, 0x00, 0x0b, 0x64, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x02, 0x00, 0x14, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x73, 0x75, 0x63, 0x63, 0x65, 0x65, 0x64, 0x65, 0x64, 0x00, 0x0e, 0x6f, 0x62, 0x6a, 0x65, 0x63, 0x74, 0x45, 0x6e, 0x63, 0x6f, 0x64, 0x69, 0x6e, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Array );

			const auto& ary = amfValue->GetArray();
			Assert::AreEqual<uint32>( 4, ary->Size );
			Assert::AreEqual( L"_result", ary->GetStringAt( 0 )->Data() );
			Assert::AreEqual( 1.0, ary->GetDoubleAt( 1 ) );

			const auto& objLapped = ary->GetAt( 2 );
			Assert::IsTrue( objLapped->ValueType == AmfValueType::Object );

			const auto& obj = objLapped->GetObject();
			Assert::AreEqual( L"FMS/3,0,1,123", obj->GetNamedString( "fmsVer" )->Data() );
			Assert::AreEqual( 31.0, obj->GetNamedDouble( "capabilities" ) );

			const auto& objLapped2 = ary->GetAt( 3 );
			Assert::IsTrue( objLapped2->ValueType == AmfValueType::Object );

			const auto& obj2 = objLapped2->GetObject( );
			Assert::AreEqual( L"status", obj2->GetNamedString( "level" )->Data() );

			Assert::AreEqual( L"NetConnection.Connect.Success", obj2->GetNamedString( "code" )->Data() );
			Assert::AreEqual( L"Connection succeeded", obj2->GetNamedString( "description" )->Data() );
			Assert::AreEqual( 0.0, obj2->GetNamedDouble( "objectEncoding" ) );
		} );
	}

private:
	static void ParseTestDouble0( std::function<IAmfValue^ ( TestByteArray^ )> parseFunc )
	{
		Assert::AreEqual( 0.0, parseFunc( ref new TestByteArray{ 0, 0, 0, 0, 0, 0, 0, 0, 0 } )->GetDouble() );
	}

	static void ParseTestObjectNull( std::function<IAmfValue^ ( TestByteArray^ )> parseFunc )
	{
		Assert::AreEqual<uint32>( 0, parseFunc( ref new TestByteArray{ 3, 0, 0, 9 } )->GetObject()->Size );
	}

	static void ParseTestArrayNull( std::function<IAmfValue^ ( TestByteArray^ )> parseFunc )
	{
		Assert::AreEqual<uint32>( 0, parseFunc( ref new TestByteArray{ 10, 0, 0, 0, 0 } )->GetArray()->Size );
	}

	static AmfValue^ ValueParse( TestByteArray^ byteArray )
	{
		return AmfValue::Parse( byteArray, AmfEncodingType::Amf0 );
	}

	static AmfValue^ ValueTryParse( TestByteArray^ byteArray )
	{
		AmfValue^ outValue;
		AmfValue::TryParse( byteArray, AmfEncodingType::Amf0, &outValue );
		return outValue;
	}

	static AmfObject^ ObjectParse( TestByteArray^ byteArray )
	{
		return AmfObject::Parse( byteArray, AmfEncodingType::Amf0 );
	}

	static AmfObject^ ObjectTryParse( TestByteArray^ byteArray )
	{
		AmfObject^ outObject;
		AmfObject::TryParse( byteArray, AmfEncodingType::Amf0, &outObject );
		return outObject;
	}

	static AmfArray^ ArrayParse( TestByteArray^ byteArray )
	{
		return AmfArray::Parse( byteArray, AmfEncodingType::Amf0 );
	}

	static AmfArray^ ArrayTryParse( TestByteArray^ byteArray )
	{
		AmfArray^ outArray;
		AmfArray::TryParse( byteArray, AmfEncodingType::Amf0, &outArray );
		return outArray;
	}


	static void TestAmf0( TestByteArray^ rawData, std::function<void( IAmfValue^ )> checkHandler )
	{
		auto r = Amf0Parser::Parse( rawData );
		auto st = r->ToString();
		checkHandler( r );
		const auto& create_data = Amf0Sequencer::Sequenceify( r );

		Assert::IsTrue( ArrayEquals( rawData, create_data ) );
	}

	static bool ArrayEquals( const Platform::Array<uint8>^ firstArray, const Platform::Array<uint8>^ secondArray )
	{
		if( firstArray->Length != secondArray->Length )
			return false;
		for( auto i = 0u; i < firstArray->Length; ++i )
		{
			if( !secondArray[i].Equals( secondArray[i] ) )
			{
				return false;
			}
		}
		return true;
	}
};