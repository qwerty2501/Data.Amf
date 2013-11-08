﻿#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( Amf3UnitTest )
{
public:
	TEST_METHOD( Amf3_⓪UndefinedTest )
	{
		Test( ref new U8Array{ 0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Undefined );
		} );
	}

	TEST_METHOD( Amf3_①NullTest )
	{
		Test( ref new U8Array{ 1 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Null );
		} );
	}

	TEST_METHOD( Amf3_②BooleanFalseTest )
	{
		Test( ref new U8Array{ 2 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Boolean );
			Assert::IsFalse( val->GetBoolean() );
		} );
	}

	TEST_METHOD( Amf3_③BooleanTrueTest )
	{
		Test( ref new U8Array{ 3 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Boolean );
			Assert::IsTrue( val->GetBoolean() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐0_0 )
	{
		Test( ref new U8Array{ 4, 0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Integer );
			Assert::AreEqual<uint32>( 0, val->GetInteger() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐1_1 )
	{
		Test( ref new U8Array{ 4, 1 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Integer );
			Assert::AreEqual<uint32>( 1, val->GetInteger() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐2_127 )
	{
		Test( ref new U8Array{ 4, 0x7f }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Integer );
			Assert::AreEqual<uint32>( 127, val->GetInteger() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐3_128 )
	{
		Test( ref new U8Array{ 4, 0x81, 0x00 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Integer );
			Assert::AreEqual<uint32>( 128, val->GetInteger() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐4_16383 )
	{
		Test( ref new U8Array{ 4, 0xff, 0x7f }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Integer );
			Assert::AreEqual<uint32>( 16383, val->GetInteger() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐5_16384 )
	{
		Test( ref new U8Array{ 4, 0x81, 0x80, 0x00 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Integer );
			Assert::AreEqual<uint32>( 16384, val->GetInteger() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐6_2097151 )
	{
		Test( ref new U8Array{ 4, 0xff, 0xff, 0x7f }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Integer );
			Assert::AreEqual<uint32>( 2097151, val->GetInteger() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐7_2097152 )
	{
		Test( ref new U8Array{ 4, 0x80, 0xc0, 0x80, 0x00 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Integer );
			Assert::AreEqual<uint32>( 2097152, val->GetInteger() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐8_536870911 )
	{
		Test( ref new U8Array{ 4, 0xff, 0xff, 0xff, 0xff }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Integer );
			Assert::AreEqual<uint32>( 536870911, val->GetInteger() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐9_Ex～536870912 )
	{
		const auto& val = AmfValue::CreateIntegerValue( 536870912 );
		FailureExceptionTest( val );
	}

	TEST_METHOD( Amf3_④IntegerTest‐a_Ex～4294967295 )
	{
		const auto& val = AmfValue::CreateIntegerValue( 4294967295 );
		FailureExceptionTest( val );
	}

	TEST_METHOD( Amf3_⑤DoubleTest‐0_0．0 )
	{
		Test( ref new U8Array{ 5, 0, 0, 0, 0, 0, 0, 0, 0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Double );
			Assert::AreEqual( 0.0, val->GetDouble() );
		} );
	}

	TEST_METHOD( Amf3_⑤DoubleTest‐1_0．5 )
	{
		Test( ref new U8Array{ 5, 0x3f, 0xe0, 0, 0, 0, 0, 0, 0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Double );
			Assert::AreEqual( 0.5, val->GetDouble() );
		} );
	}

	TEST_METHOD( Amf3_⑥StringTest‐0_Null )
	{
		Test( ref new U8Array{ 6, 1 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::String );
			Assert::AreEqual( val->GetString()->Data(), L"" );
		} );
	}

	TEST_METHOD( Amf3_⑥StringTest‐1_Ascii )
	{
		Test( ref new U8Array{ 6, 11, 0x41, 0x53, 0x43, 0x49, 0x49 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::String );
			Assert::AreEqual( val->GetString()->Data(), L"ASCII" );
		} );
	}

	TEST_METHOD( Amf3_⑥StringTest‐2_RandomCharactors1 )
	{
		Test( ref new U8Array{ 6, 13, 0xc2, 0xbd, 0x3a, 0x20, 0x32, 0x42 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::String );
			Assert::AreEqual( L"½: 2B", val->GetString()->Data() );
		} );
	}

	TEST_METHOD( Amf3_⑥StringTest‐3_RandomCharactors2 )
	{
		Test( ref new U8Array{ 6, 15, 0xe2, 0x91, 0xb4, 0x3a, 0x20, 0x33, 0x42 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::String );
			Assert::AreEqual( L"⑴: 3B", val->GetString()->Data() );
		} );
	}

	TEST_METHOD( Amf3_⑦XmlDocumentTest‐0_RootNode )
	{
		ParserTest( ref new U8Array{ 7, 13, 0x3c, 0x72, 0x6f, 0x6f, 0x74, 0x3e }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Xml );
			Assert::AreEqual( L"<root>", val->GetString()->Data() );
		} );
	}

	TEST_METHOD( Amf3_⑧DateTest‐0_2013／10／13 )
	{
		Test( ref new U8Array{ 8, 1, 0x42, 0x74, 0x1a, 0xd2, 0xe6, 0x18, 0x00, 0x00 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Date );

			const auto& exp = AssertHelper::GetDate( 2013, 10, 13 );
			Assert::IsTrue( exp.UniversalTime == val->GetDate().UniversalTime );
		} );
	}

	TEST_METHOD( Amf3_⑧DateTest‐1_2013／11／02_20：28：52．0100 )
	{
		Test( ref new U8Array{ 8, 1, 0x42, 0x74, 0x21, 0x89, 0x2a, 0x18, 0x40, 0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Date );

			const auto& exp = AssertHelper::GetDate( 2013, 11, 2, 20, 28, 52, 100 * 1000000 );
			Assert::IsTrue( exp.UniversalTime == val->GetDate().UniversalTime );
		} );
	}

	TEST_METHOD( Amf3_⑧DateTest‐2_2013／11／02_20：28：52．0100AndRef )
	{
		Test( ref new U8Array{ 9, 0x5, 0x1, 0x8, 0x1, 0x42, 0x74, 0x21, 0x89, 0x2a, 0x18, 0x40, 0x0, 0x8, 0x2 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Array );

			const auto& ary = val->GetArray();
			const auto& exp = AssertHelper::GetDate( 2013, 11, 2, 20, 28, 52, 100 * 1000000 );
			Assert::IsTrue( exp.UniversalTime == ary->GetDateAt( 0 ).UniversalTime );
			Assert::IsTrue( exp.UniversalTime == ary->GetDateAt( 1 ).UniversalTime );
		} );
	}

	TEST_METHOD( Amf3_⑨ArrayTest‐0_NumKeyAndStrKey )
	{
		Test( ref new U8Array{ 9, 0x3, 0x7, 0x61, 0x62, 0x63, 0x4, 0x3, 0x1, 0x4, 0x2 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::EcmaArray );

			const auto& obj = val->GetObject();
			const auto& num = obj->GetNamedInteger( "0" );
			Assert::AreEqual<uint32>( 2, num );

			const auto& str = obj->GetNamedInteger( "abc" );
			Assert::AreEqual<uint32>( 3, str );
		} );
	}

	TEST_METHOD( Amf3_⑨ArrayTest‐1_NumKeyOnly )
	{
		Test( ref new U8Array{ 9, 0x5, 0x1, 0x4, 0x2, 0x4, 0x3 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Array );

			const auto& ary = val->GetArray();
			const auto& num0 = ary->GetIntegerAt( 0 );
			Assert::AreEqual<uint32>( 2, num0 );

			const auto& num1 = ary->GetIntegerAt( 1 );
			Assert::AreEqual<uint32>( 3, num1 );
		} );
	}

	TEST_METHOD( Amf3_⑨ArrayTest‐2_StrKeyOnly )
	{
		Test( ref new U8Array{ 9, 0x1, 0x7, 0x78, 0x79, 0x7a, 0x4, 0x3, 0x7, 0x61, 0x62, 0x63, 0x4, 0x2, 0x1 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::EcmaArray );

			const auto& obj = val->GetObject();
			const auto& strAbc = obj->GetNamedInteger( "abc" );
			Assert::AreEqual<uint32>( 2, strAbc );

			const auto& strXyz = obj->GetNamedInteger( "xyz" );
			Assert::AreEqual<uint32>( 3, strXyz );
		} );
	}

	TEST_METHOD( Amf3_⑨ArrayTest‐3_HasOneRefStrValue )
	{
		Test( ref new U8Array{ 9, 0x1, 0x7, 0x61, 0x62, 0x63, 0x6, 0x0, 0x7, 0x78, 0x79, 0x7a, 0x4, 0x3, 0x1 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::EcmaArray );

			const auto& obj = val->GetObject();
			const auto& strAbc = obj->GetNamedString( "abc" );
			Assert::AreEqual( L"abc", strAbc );

			const auto& strXyz = obj->GetNamedInteger( "xyz" );
			Assert::AreEqual<uint32>( 3, strXyz );
		} );
	}

	TEST_METHOD( Amf3_⑨ArrayTest‐4_HasSomeRefStrValue )
	{
		Test( ref new U8Array{ 9, 0x7, 0x7, 0x78, 0x79, 0x7a, 0x6, 0x9, 0x70, 0x71, 0x72, 0x73, 0x1, 0x6, 0x7, 0x61, 0x62, 0x63, 0x6, 0x0, 0x6, 0x2 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::EcmaArray );

			const auto& obj = val->GetObject();
			const auto& str0 = obj->GetNamedString( "0" );
			Assert::AreEqual( L"abc", str0 );

			const auto& str1 = obj->GetNamedString( "1" );
			Assert::AreEqual( L"xyz", str1 );

			const auto& str2 = obj->GetNamedString( "2" );
			Assert::AreEqual( L"pqrs", str2 );

			const auto& strXyz = obj->GetNamedString( "xyz" );
			Assert::AreEqual( L"pqrs", strXyz );
		} );
	}

	TEST_METHOD( Amf3_⑩ObjectTest‐0_Default )
	{
		Test( ref new U8Array{ 10, 0xb, 0x1, 0x3, 0x62, 0x4, 0x3, 0x3, 0x61, 0x4, 0x2, 0x1 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Object );

			const auto& obj = val->GetObject();
			const auto& a = obj->GetNamedInteger( "a" );
			Assert::AreEqual<uint32>( 2, a );

			const auto& b = obj->GetNamedInteger( "b" );
			Assert::AreEqual<uint32>( 3, b );
		} );
	}

	TEST_METHOD( Amf3_⑪XmlTest‐0_RootNode )
	{
		Test( ref new U8Array{ 11, 13, 0x3c, 0x72, 0x6f, 0x6f, 0x74, 0x3e }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Xml );
			Assert::AreEqual( L"<root>", val->GetString()->Data() );
		} );
	}

	TEST_METHOD( Amf3_⑫ByteArrayTest‐0_234 )
	{
		Test( ref new U8Array{ 12, 0x7, 0x2, 0x3, 0x4 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::ByteArray );

			const auto& ba = val->GetByteArray();
			AssertHelper::AreArrayEqual( ref new U8Array{ 2, 3, 4 }, ba );
		} );
	}

	TEST_METHOD( Amf3_⑬VectorIntTest‐0_2／3 )
	{
		Test( ref new U8Array{ 13, 0x5, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x3 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::VectorInt );

			const auto& vi = val->GetVectorInt();
			Assert::AreEqual( 2, vi->GetAt( 0 ) );
			Assert::AreEqual( 3, vi->GetAt( 1 ) );
		} );
	}

	TEST_METHOD( Amf3_⑭VectorUintTest‐0_2／3 )
	{
		Test( ref new U8Array{ 14, 0x5, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x3 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::VectorUint );

			const auto& vu = val->GetVectorUint();
			Assert::AreEqual( 2u, vu->GetAt( 0 ) );
			Assert::AreEqual( 3u, vu->GetAt( 1 ) );
		} );
	}

	TEST_METHOD( Amf3_⑮VectorDoubleTest‐0_2．0／3．0 )
	{
		Test( ref new U8Array{ 15, 0x5, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::VectorDouble );

			const auto& vd = val->GetVectorDouble();
			Assert::AreEqual( 2.0, vd->GetAt( 0 ) );
			Assert::AreEqual( 3.0, vd->GetAt( 1 ) );
		} );
	}

	TEST_METHOD( Amf3_ⓍMasterTest_RtmpCommandData )
	{
		Test( ref new U8Array{ 0x9, 0x9, 0x1, 0x6, 0xf, 0x5f, 0x72, 0x65, 0x73, 0x75, 0x6c, 0x74, 0x4, 0x1, 0xa, 0xb, 0x1, 0x19, 0x63, 0x61, 0x70, 0x61, 0x62, 0x69, 0x6c, 0x69, 0x74, 0x69, 0x65, 0x73, 0x4, 0x1f, 0xd, 0x66, 0x6d, 0x73, 0x56, 0x65, 0x72, 0x6, 0x1b, 0x46, 0x4d, 0x53, 0x2f, 0x33, 0x2c, 0x30, 0x2c, 0x31, 0x2c, 0x31, 0x32, 0x33, 0x1, 0xa, 0x1, 0x17, 0x64, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x6, 0x29, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x73, 0x75, 0x63, 0x63, 0x65, 0x65, 0x64, 0x65, 0x64, 0x1d, 0x6f, 0x62, 0x6a, 0x65, 0x63, 0x74, 0x45, 0x6e, 0x63, 0x6f, 0x64, 0x69, 0x6e, 0x67, 0x4, 0x0, 0x9, 0x63, 0x6f, 0x64, 0x65, 0x6, 0x3b, 0x4e, 0x65, 0x74, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x2e, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x2e, 0x53, 0x75, 0x63, 0x63, 0x65, 0x73, 0x73, 0xb, 0x6c, 0x65, 0x76, 0x65, 0x6c, 0x6, 0xd, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73, 0x1 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Array );

			const auto& ary = val->GetArray();
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

			const auto& obj2 = objLapped2->GetObject();
			Assert::AreEqual( L"status", obj2->GetNamedString( "level" )->Data() );
			Assert::AreEqual( L"NetConnection.Connect.Success", obj2->GetNamedString( "code" )->Data() );
			Assert::AreEqual( L"Connection succeeded", obj2->GetNamedString( "description" )->Data() );
			Assert::AreEqual( 0.0, obj2->GetNamedDouble( "objectEncoding" ) );
		} );
	}

private:
	void Test( U8Array^ expected, std::function<void( IAmfValue^ )> checkHandler )
	{
		const auto& amf = ParserTest( expected, checkHandler );
		const auto& createData = SequencerTest( amf );
		AssertHelper::AreArrayEqual( expected, createData );
	}

	IAmfValue^ ParserTest( U8Array^ expected, std::function<void( IAmfValue^ )> checkHandler )
	{
		const auto& amf = Amf3Parser::Parse( expected );
		const auto& str = amf->ToString();
		Logger::WriteMessage( str->Data() );
		checkHandler( amf );
		return amf;
	}

	U8Array^ SequencerTest( IAmfValue^ val )
	{
		return Amf3Sequencer::Sequencify( val );
	}

	void FailureExceptionTest( IAmfValue^ val )
	{
		Assert::ExpectException<Platform::FailureException^>( [=]
		{
			SequencerTest( val );
		} );
	}
};