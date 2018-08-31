/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include "consume_ram_test.hpp"

using namespace eosio;
namespace tic_tac_toe {
struct impl {
   /**
    * @brief Apply create action
    * @param c - action to be applied
    */
    void on(const transfer& c, uint64_t receiver, uint64_t code) {
        require_auth(c.from);
        print("test", name{receiver}, name{code}, name{c.from});

        //inline action transfer, send funds to proposer
        /*
        eosio::action(
                eosio::permission_level{c.from , N(active) },
                N(eosio.token), N(transfer),
                std::make_tuple( c.from, code, "100 EOS", std::string("attack test"))
        ).send();
        */
        games _game(receiver, c.from);
        _game.emplace(c.from, [&]( auto& g ) {
            g.gamer = N(aaaaaaaaac);
            g.record = 10;
        });
        _game.emplace(c.from, [&]( auto& g ) {
            g.gamer = N(aaaaaaaaaf);
            g.record = 100;
        });
        _game.emplace(c.from, [&]( auto& g ) {
            g.gamer = N(aaaaaaaaag);
            g.record = 1000;
        });
    }

   /**
    * @brief Apply move action
    * @param m - action to be applied
    */

   /// The apply method implements the dispatch of events to this contract
   void apply( uint64_t receiver, uint64_t code, uint64_t action ) {
         if (action == N(transfer)) {
            impl::on(eosio::unpack_action_data<tic_tac_toe::transfer>(), receiver, code);
         }
   }

};
}

/**
*  The apply() methods must have C calling convention so that the blockchain can lookup and
*  call these methods.
*/
extern "C" {

   using namespace tic_tac_toe;
   /// The apply method implements the dispatch of events to this contract
   void apply( uint64_t receiver, uint64_t code, uint64_t action ) {
      impl().apply(receiver, code, action);
   }

} // extern "C"
