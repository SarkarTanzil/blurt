#include <iostream>
#include "qam.h"
#include "cc.h"
#include <stdint.h>

int main(int argc, char **argp, char **envp) {
    QAM qam(6);
    complex input_data[100] = {
        complex( 0.87351053,-2.95107652), complex( 0.60034215,+0.14694272), complex(-1.19640623,-0.47464486), complex(-2.02080161,-1.41166226),
        complex( 1.03313946,-0.19951225), complex( 0.65292322,-0.99240952), complex( 0.39455197,+0.88894462), complex(-2.32675700,+0.75269158),
        complex( 0.30703731,+0.73947274), complex( 0.70779968,-0.72681016), complex(-0.69749069,-0.6045121 ), complex(-1.44326153,+0.43052726),
        complex( 2.27914784,+1.00035343), complex(-1.24746453,+1.72455107), complex(-0.17986871,+2.26728032), complex( 0.03801843,-1.27790702),
        complex(-1.08354180,-1.01978816), complex(-0.07637488,+0.57436651), complex(-0.02141504,-0.00727353), complex( 0.04796216,+1.13155349),
        complex( 1.45357037,-0.4483743 ), complex(-0.00995999,+0.3316014 ), complex(-1.90402664,-0.06391367), complex( 2.06535343,+0.02664987),
        complex(-0.52918961,-0.91798425), complex(-0.14026426,-0.35632188), complex(-0.99835227,-1.05221545), complex(-1.66456313,+1.79217667),
        complex( 0.45650177,+0.66967068), complex(-0.43476077,+2.47767218), complex( 0.21031763,-2.0176462 ), complex( 0.75248673,-0.91604597),
        complex(-0.47463845,-1.42891522), complex(-1.61035932,+0.22927885), complex( 1.76271857,-1.40973838), complex( 0.63364543,+0.25704748),
        complex( 0.32619478,+0.65981761), complex(-0.61687687,+0.9702851 ), complex( 0.31910748,+2.54295236), complex(-0.89557074,+0.8231933 ),
        complex(-0.37118441,-2.06253352), complex( 2.81427286,+0.6644789 ), complex( 0.71777549,-0.45843965), complex( 0.89775887,+0.0096148 ),
        complex( 0.87830786,+1.40824623), complex( 0.05108756,+0.77749252), complex( 0.28010627,+0.26801436), complex(-1.53474072,-0.38874837),
        complex(-0.86804994,-2.3009836 ), complex(-0.71961034,-1.15304111), complex(-0.12521538,+0.39382101), complex(-0.50710618,-0.4284931 ),
        complex( 2.26274222,+0.81182967), complex( 0.75974627,-0.851087  ), complex(-0.68041070,-0.75012347), complex(-0.96919476,+0.44213527),
        complex(-0.05751708,+1.10738926), complex( 1.56753223,+0.11687475), complex(-0.31128422,+0.42785957), complex(-0.01618886,-1.2730451 ),
        complex(-0.09857617,-1.90462792), complex( 0.22958359,+0.62462007), complex( 0.16064812,-0.94515931), complex( 0.61267470,-1.05409171),
        complex(-1.16567938,-0.89689886), complex( 1.80449173,-0.21205592), complex(-0.38747244,-0.73292489), complex(-0.17230702,+0.01511152),
        complex( 0.17065298,+0.6078246 ), complex( 0.53439949,+0.25044288), complex( 1.54373867,-2.2624264 ), complex(-1.35082417,-0.36510594),
        complex(-0.62585313,+0.11578502), complex( 2.53108388,-0.68336614), complex(-0.18053351,-1.08540093), complex( 0.62649195,+0.67571308),
        complex( 0.02427898,-0.67566988), complex( 0.16958161,-0.55258059), complex( 1.09205389,+0.71080559), complex( 0.57920124,+1.13002358),
        complex(-1.82470468,-0.32009046), complex( 0.38723381,-0.23957747), complex( 0.06269822,-2.84699975), complex(-0.64593282,-1.15890878),
        complex( 1.20419633,-1.06219036), complex( 0.05175541,-0.21549287), complex( 1.45470638,-0.72627929), complex(-0.18786357,+0.26373133),
        complex(-0.21134584,+0.51017608), complex( 1.49820809,-2.33701051), complex( 0.14103132,-0.52968968), complex(-1.14697371,-0.26542972),
        complex(-1.02078161,-1.36819908), complex( 1.58809995,-0.37136348), complex( 1.00979013,-1.36779781), complex( 0.13537942,+0.32244865),
        complex( 0.68138584,-0.63996865), complex( 1.12028303,+0.68770766), complex( 0.63475950,+2.17537916), complex(-0.11605853,+1.84150574)
    };
    std::vector<complex> input;
    input.assign(input_data, input_data+sizeof(input_data)/sizeof(input_data[0]));
    //std::vector<int> output;
    //qam.demap(input, 1.f, output);
    bool bits[] = {1,0,0,1,0,0,1,1,1,1,1,0,0,0,0,0,0};
    std::vector<bool> inputBits;
    std::vector<bool> outputBits;
    inputBits.assign(bits, bits+sizeof(bits)/sizeof(bits[0]));
    ConvolutionalCode cc(7, 0133, 0171);
    cc.encode(inputBits, outputBits);
    std::vector<int> inputLL(outputBits.size());
    std::vector<bool> recoveredBits;
    for (int i=0; i<outputBits.size(); i++) {
        inputLL[i] = (int)outputBits[i] * 2 - 1;
    }
    cc.decode(inputLL, inputBits.size()-6, recoveredBits);
    for (int i=0; i<recoveredBits.size(); i++) {
        std::cout << recoveredBits[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}