#pragma once
#include "IAmfValue.h"

namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::DualApiPartition( version = NTDDI_WIN8 )]
	[Windows::Foundation::Metadata::MarshalingBehavior( Windows::Foundation::Metadata::MarshalingType::Agile )]
	[Windows::Foundation::Metadata::Threading( Windows::Foundation::Metadata::ThreadingModel::Both )]
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class AmfValue sealed:
		public IAmfValue
	{
	public:
		AmfValue( void );

		// IAmfValue
		virtual Platform::Array<uint8>^ Sequenceify( void );
		virtual Platform::Array<uint8>^ Sequenceify( AmfEncodingType type );
		virtual bool GetBoolean( void );
		virtual float64 GetDouble( void );
		virtual int32 GetInteger( void );
		virtual Platform::String^ GetString( void );
		virtual Windows::Foundation::DateTime GetDate( void );
		virtual Platform::Array<uint8>^ GetByteArray( void );
		virtual Windows::Foundation::Collections::IVector<int32>^ GetVectorInt( void );
		virtual Windows::Foundation::Collections::IVector<uint32>^ GetVectorUint( void );
		virtual Windows::Foundation::Collections::IVector<float64>^ GetVectorDouble( void );
		virtual AmfObject^ GetObject( void );
		virtual AmfArray^ GetArray( void );

		// IStringable
		virtual Platform::String^ ToString( void ) override sealed;

		static AmfValue^ CreateUndefinedValue( void );
		static AmfValue^ CreateBooleanValue( bool input );
		static AmfValue^ CreateDoubleValue( float64 input );
		static AmfValue^ CreateIntegerValue( int32 input );
		static AmfValue^ CreateStringValue( Platform::String^ input );
		static AmfValue^ CreateDateValue( Windows::Foundation::DateTime input );
		static AmfValue^ CreateXmlValue( Platform::String^ input );
		static AmfValue^ CreateByteArrayValue( const Platform::Array<uint8>^ input );
		static AmfValue^ CreateVectorIntValue( Windows::Foundation::Collections::IVector<int32>^ input );
		static AmfValue^ CreateVectorUintValue( Windows::Foundation::Collections::IVector<uint32>^ input );
		static AmfValue^ CreateVectorDoubleValue( Windows::Foundation::Collections::IVector<float64>^ input );

		static AmfValue^ Parse( const Platform::Array<uint8>^ input );
		static AmfValue^ Parse( const Platform::Array<uint8>^ input, AmfEncodingType type );
		static bool TryParse( const Platform::Array<uint8>^ input, AmfValue^* result );
		static bool TryParse( const Platform::Array<uint8>^ input, AmfEncodingType type, AmfValue^* result );

	internal:
		static AmfValue^ CreateByteArrayValue( std::vector<uint8> input );

	public:
		// IAmfValue
		property AmfValueType ValueType
		{
			virtual AmfValueType get( void ) { return ValueType_; }
		}

	private:
		AmfValueType ValueType_;
		Platform::Object^ value_;
	};

} } }
