#include "header/Controller.h"

Controller::Controller(modelSql *model, View *view){
    this->m = model;
    this->v = view;
    http_request req;
    this->mp = new mapParams();
    this->listener = http_listener(this->URL);
    this->listener.support(methods::GET,std::bind(&Controller::handleGet, this, std::placeholders::_1));
    this->listener.support(methods::POST,std::bind(&Controller::handlePost, this, std::placeholders::_1));
    this->listener.support(methods::PUT,std::bind(&Controller::handlePut, this, std::placeholders::_1));
    this->listener.support(methods::DEL,std::bind(&Controller::handleDel, this, std::placeholders::_1));
    try
    {
        listener.open().then([this]() { cout << "starting to listen" << endl << "..." << endl << endl; }).wait();
        std::async(update_day);
        while (true);
    }
    catch (exception const &e)
    {
        wcout << e.what() << endl;
    }
}

Controller::~Controller(){

}

mapParams&  Controller::splitParamsQuery(string paramsQuery){
string delimiter_a= "=";
string delimiter_b= "&";
string delimiter_c= ";"; //%2C = , //%3B = ;
size_t pos = 0; 
string token_k;
string token_v;
    /*
     * funzione find restituisce la posizione della prima occorrenza di str nella stringa o npos se la stringa non viene trovata.
     * La substr(size_t pos = 0, size_t n = npos)funzione restituisce una sottostringa dell'oggetto, a partire dalla posizione pos e dalla lunghezza npos
     * Se hai più delimitatori, dopo aver estratto un token, puoi rimuoverlo (delimitatore incluso) per procedere con le estrazioni successive 
     * (se vuoi conservare la stringa originale, usa semplicemente s = s.substr(pos + delimiter.length());)
     */
    if((pos=paramsQuery.find(delimiter_a))!= std::string::npos){   //id=id1;id2&i=id3
        token_k = paramsQuery.substr(0, pos); //token_k= id
        pos=pos + delimiter_a.length();
        paramsQuery.erase(0, pos);                                  //paramsQuery = id1%3Bid2&i=id3
        if(paramsQuery.find(delimiter_c)){
            token_v = paramsQuery;                                  //token_v = id1%3Bid2&i=id3
            if((pos=paramsQuery.find(delimiter_b))!= std::string::npos){       
                pos= pos + delimiter_b.length();
                token_v.erase(pos-1);        
            }
        }
        else token_v = paramsQuery.substr(0, pos);    
        this->mp->insertParam(token_k,token_v);
        if((pos=paramsQuery.find(delimiter_b))!= std::string::npos){       
            pos= pos + delimiter_b.length();
            splitParamsQuery(paramsQuery.erase(0, pos));      
        }
    }
    else{
        token_k= paramsQuery;
        this->mp->insertParam(token_k,"");    
    }
    return *this->mp; 
}

void Controller::handleGet(http_request request){
    cout << "Received GET request" << endl;
    auto abs_uri = request.absolute_uri();
    auto params = abs_uri.query().c_str();
    string params_string="";
    params_string = string(params);
    mapParams mapP = splitParamsQuery(params_string);
    mapP.printParams(); 
    mapParams mapR = this->m->select(mapP);
    this->v->response(request, mapR.getMap());
    //clear map's modelSql (map's response query)
    this->m->clearMap();
    //clear map generated from splitParamsQuery
    this->mp->clearMap();
    return;
}


void Controller::handlePost(http_request request){
    cout << "Received POST request" << endl;
    auto abs_uri = request.absolute_uri();
    auto params = abs_uri.query().c_str();
    string params_string="";
    params_string = string(params);
    mapParams mapP = splitParamsQuery(params_string);
    mapP.printParams(); 
    mapParams mapR = this->m->insert(mapP);
    this->v->response(request, mapR.getMap());
    //clear map's modelSql (map's response query)
    this->m->clearMap();
    //clear map generated from splitParamsQuery
    this->mp->clearMap();
    return;
}


void Controller::handlePut(http_request request){
    cout << "Received PUT request" << endl;
    auto abs_uri = request.absolute_uri();
    auto params = abs_uri.query().c_str();
    string params_string="";
    params_string = string(params);
    mapParams mapP = splitParamsQuery(params_string);
    mapP.printParams(); 
    mapParams mapR = this->m->update(mapP);
    this->v->response(request, mapR.getMap());
    //clear map's modelSql (map's response query)
    this->m->clearMap();
    //clear map generated from splitParamsQuery
    this->mp->clearMap();  
    return;
}


void Controller::handleDel(http_request request){
    cout << "Received DELETE request" << endl;
    auto abs_uri = request.absolute_uri();
    auto params = abs_uri.query().c_str();
    string params_string="";
    params_string = string(params);
    mapParams mapP = splitParamsQuery(params_string);
    mapP.printParams(); 
    mapParams mapR = this->m->deleteRow(mapP);
    this->v->response(request, mapR.getMap());
    //clear map's modelSql (map's response query)
    this->m->clearMap();
    //clear map generated from splitParamsQuery
    this->mp->clearMap();
    return;
}