#include "formsblockgfm.h"
#include <QtZlib/zlib.h>

#include <QFile>

bool gzipCompress(QByteArray input, QByteArray &output, int level){
    output.clear();
    if(input.length()){
        int flush = 0;
        z_stream strm;
        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        strm.avail_in = 0;
        strm.next_in = Z_NULL;
        int ret = deflateInit2(&strm, qMax(-1, qMin(9, level)), Z_DEFLATED, 31, 8, Z_DEFAULT_STRATEGY);
        if (ret != Z_OK)
            return(false);
        output.clear();
        char *input_data = input.data();
        int input_data_left = input.length();
        do {
            int chunk_size = qMin(32768, input_data_left);
            strm.next_in = (unsigned char*)input_data;
            strm.avail_in = chunk_size;
            input_data += chunk_size;
            input_data_left -= chunk_size;
            flush = (input_data_left <= 0 ? Z_FINISH : Z_NO_FLUSH);
            do {
                char out[32768];
                strm.next_out = (unsigned char*)out;
                strm.avail_out = 32768;
                ret = deflate(&strm, flush);
                if(ret == Z_STREAM_ERROR){
                    deflateEnd(&strm);
                    return(false);
                }
                int have = (32768 - strm.avail_out);
                if(have > 0)
                    output.append((char*)out, have);
            } while (strm.avail_out == 0);
        } while (flush != Z_FINISH);
        (void)deflateEnd(&strm);
        return(ret == Z_STREAM_END);
    }
    else
        return(true);
}
bool gzipDecompress(QByteArray input, QByteArray &output){
    output.clear();
    if(input.length() > 0){
        z_stream strm;
        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        strm.avail_in = 0;
        strm.next_in = Z_NULL;
        int ret = inflateInit2(&strm, 31);

        if (ret != Z_OK)
            return(false);
        char *input_data = input.data();
        int input_data_left = input.length();
        do {
            int chunk_size = qMin(32768, input_data_left);
            if(chunk_size <= 0)
                break;
            strm.next_in = (unsigned char*)input_data;
            strm.avail_in = chunk_size;
            input_data += chunk_size;
            input_data_left -= chunk_size;
            do {
                char out[32768];
                strm.next_out = (unsigned char*)out;
                strm.avail_out = 32768;
                ret = inflate(&strm, Z_NO_FLUSH);

                switch (ret) {
                case Z_NEED_DICT:
                    ret = Z_DATA_ERROR;
                case Z_DATA_ERROR:
                case Z_MEM_ERROR:
                case Z_STREAM_ERROR:
                    inflateEnd(&strm);
                    return(false);
                }
                int have = (32768 - strm.avail_out);
                if(have > 0)
                    output.append((char*)out, have);
            } while (strm.avail_out == 0);
        } while (ret != Z_STREAM_END);
        inflateEnd(&strm);
        return (ret == Z_STREAM_END);
    }
    else
        return(true);
}

FormsBlockGFM::FormsBlockGFM(){
    m_forms = nullptr;
}

Forms *FormsBlockGFM::forms(){
    return m_forms;
}

void FormsBlockGFM::parser(QByteArray *bodyBlock){
    if(bodyBlock->isEmpty())
        return;
      QByteArray out;
      if(!gzipDecompress(*bodyBlock,out)){
          qDebug() <<  "Не удалось расшифровать формы";
          return;
      }

      int indexBeginVersion = out.indexOf("version=\"") + QByteArray("version=\"").size();
      int indexEndVersion = out.indexOf("\"",indexBeginVersion);
      m_version = out.mid(indexBeginVersion,indexEndVersion - indexBeginVersion);
      int indexBeginEncoding = out.indexOf("encoding=\"") + QByteArray("encoding=\"").size();
      int indexEndEncoding = out.indexOf("\"",indexBeginEncoding);
      m_encoding = out.mid(indexBeginEncoding,indexEndEncoding - indexBeginEncoding);
      int indexBeginForms = out.indexOf("<forms");
      int indexEndForms = out.indexOf("</forms>") + QByteArray("</forms>").size();
      QByteArray formsByteArray = out.mid(indexBeginForms,indexEndForms - indexBeginForms);
      m_forms = new Forms(formsByteArray);
}

bool FormsBlockGFM::isReady(){
    if(m_forms)
        return m_forms->isReady();
    else {
        return true;
    }
}

QByteArray FormsBlockGFM::getForSave(){
    return nullptr;
}

FormsBlockGFM::~FormsBlockGFM(){

}
