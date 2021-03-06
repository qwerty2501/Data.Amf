#include "pch.h"
#include "AmfArray.h"
#include "Amf0Parser.h"
#include "Amf0Sequencer.h"
#include "Amf3Parser.h"

using namespace Mntone::Data::Amf;

AmfArray::AmfArray( void ) :
	ValueType_( AmfValueType::Array ),
	Strict_( false ),
	vector_( ref new Platform::Collections::Vector<IAmfValue^>() )
{ }

Platform::Array<uint8>^ AmfArray::Sequenceify( void )
{
	throw ref new Platform::NotImplementedException();
}

Platform::Array<uint8>^ AmfArray::Sequenceify( AmfEncodingType type )
{
	if( type == AmfEncodingType::Amf0 )
		return Amf0Sequencer::Sequenceify( this );

	throw ref new Platform::NotImplementedException();
}

bool AmfArray::GetBoolean( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
float64 AmfArray::GetDouble( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
int32 AmfArray::GetInteger( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
Platform::String^ AmfArray::GetString( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
Windows::Foundation::DateTime AmfArray::GetDate( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
Platform::Array<uint8>^ AmfArray::GetByteArray( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
Windows::Foundation::Collections::IVector<int32>^ AmfArray::GetVectorInt( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
Windows::Foundation::Collections::IVector<uint32>^ AmfArray::GetVectorUint( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
Windows::Foundation::Collections::IVector<float64>^ AmfArray::GetVectorDouble( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
AmfObject^ AmfArray::GetObject( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
AmfArray^ AmfArray::GetArray( void ) { return safe_cast<AmfArray^>( this ); }

bool AmfArray::GetBooleanAt( uint32 index ) { return vector_->GetAt( index )->GetBoolean(); }
float64 AmfArray::GetDoubleAt( uint32 index ) { return vector_->GetAt( index )->GetDouble(); }
int32 AmfArray::GetIntegerAt( uint32 index ) { return vector_->GetAt( index )->GetInteger(); }
Platform::String^ AmfArray::GetStringAt( uint32 index ) { return vector_->GetAt( index )->GetString(); }
Windows::Foundation::DateTime AmfArray::GetDateAt( uint32 index ) { return vector_->GetAt( index )->GetDate(); }
Platform::Array<uint8>^ AmfArray::GetByteArrayAt( uint32 index ) { return vector_->GetAt( index )->GetByteArray(); }
Windows::Foundation::Collections::IVector<int32>^ AmfArray::GetVectorIntAt( uint32 index ) { return vector_->GetAt( index )->GetVectorInt(); }
Windows::Foundation::Collections::IVector<uint32>^ AmfArray::GetVectorUintAt( uint32 index ) { return vector_->GetAt( index )->GetVectorUint(); }
Windows::Foundation::Collections::IVector<float64>^ AmfArray::GetVectorDoubleAt( uint32 index ) { return vector_->GetAt( index )->GetVectorDouble(); }
AmfObject^ AmfArray::GetObjectAt( uint32 index ) { return vector_->GetAt( index )->GetObject(); }
AmfArray^ AmfArray::GetArrayAt( uint32 index ) { return vector_->GetAt( index )->GetArray(); }

Windows::Foundation::Collections::IIterator<IAmfValue^>^ AmfArray::First( void ) { return vector_->First(); }

IAmfValue^ AmfArray::GetAt( uint32 index ) { return vector_->GetAt( index ); }
Windows::Foundation::Collections::IVectorView<IAmfValue^>^ AmfArray::GetView( void ) { return vector_->GetView(); }
bool AmfArray::IndexOf( IAmfValue^ value, uint32 *index ) { return vector_->IndexOf( value, index ); }

void AmfArray::SetAt( uint32 index, IAmfValue^ value ) { vector_->SetAt( index, value ); }
void AmfArray::InsertAt( uint32 index, IAmfValue^ value ) { vector_->InsertAt( index, value ); }
void AmfArray::RemoveAt( uint32 index ) { vector_->RemoveAt( index ); }
void AmfArray::Append( IAmfValue^ value ) { vector_->Append( value ); }
void AmfArray::RemoveAtEnd( void ) { vector_->RemoveAtEnd(); }
void AmfArray::Clear( void ) { vector_->Clear(); }

uint32 AmfArray::GetMany( uint32 startIndex, Platform::WriteOnlyArray<IAmfValue^>^ items ) { return vector_->GetMany( startIndex, items ); }
void AmfArray::ReplaceAll( const Platform::Array<IAmfValue^>^ items ) { vector_->ReplaceAll( items ); }

Platform::String^ AmfArray::ToString( void )
{
	std::wstringstream buf;
	buf << '[';
	for( const auto& item : vector_ )
	{
		const auto& out = item->ToString();
		buf.write( out->Data(), out->Length() );
		buf.write( L", ", 2 );
	}
	buf << ']';
	return ref new Platform::String( buf.str().c_str() );
}

AmfArray^ AmfArray::CreateStrictArray( void )
{
	auto out = ref new AmfArray();
	out->Strict_ = true;
	return out;
}

AmfArray^ AmfArray::Parse( const Platform::Array<uint8>^ input )
{
	return reinterpret_cast<AmfArray^>( Amf3Parser::Parse( input ) );
}

AmfArray^ AmfArray::Parse( const Platform::Array<uint8>^ input, AmfEncodingType type )
{
	if( type == AmfEncodingType::Amf0 )
		return reinterpret_cast<AmfArray^>( Amf0Parser::Parse( input ) );

	return reinterpret_cast<AmfArray^>( Amf3Parser::Parse( input ) );
}

bool AmfArray::TryParse( const Platform::Array<uint8>^ input, AmfArray^* result )
{
	auto buf = reinterpret_cast<IAmfValue^*>( result );
	return Amf3Parser::TryParse( input, buf );
}

bool AmfArray::TryParse( const Platform::Array<uint8>^ input, AmfEncodingType type, AmfArray^* result )
{
	auto buf = reinterpret_cast<IAmfValue^*>( result );
	if( type == AmfEncodingType::Amf0 )
		return Amf0Parser::TryParse( input, buf );

	return Amf3Parser::TryParse( input, buf );
}

void AmfArray::SetData( std::vector<IAmfValue^> data )
{
	vector_ = ref new Platform::Collections::Vector<IAmfValue^>( std::move( data ) );
}