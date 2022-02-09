ll gcd(ll x,ll y){
  if(!y)return x;
  return gcd(y,x%y);
}

pair<ll,ll> ex_gcd(ll a,ll b){
  if(!b) return{1,0};
  pair<ll,ll>rec=ex_gcd(b,a%b);
  ll x=rec.second;
  ll y=rec.first-(a/b)*rec.second;
  if(x<=0){
    x+=b;
    y-=a;
  }
  return{x,y};
}
