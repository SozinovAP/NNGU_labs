package com.example.tokeniz

class EncoderDecoder(private var encoder: Map<String, Int>,
                     private var decoder: Map<Int, String>) {

    fun Encode()
    {
    }

    fun Decode(key: Int, valueDef: String): String
    {
        return decoder.getOrDefault(key, valueDef);
    }

    fun GetEncoder(): Map<String, Int>
    {
        return encoder;
    }

    fun GetEncodeByKey(str: String): Int
    {
        return encoder[str]!!;
    }

    fun GetDecoder(): Map<Int, String>
    {
        return decoder;
    }

    fun SetEncoder(encoder: Map<String, Int>)
    {
        this.encoder = encoder;
    }

    fun SetDecoder(decoder: Map<Int, String>)
    {
        this.decoder = decoder;
    }
}