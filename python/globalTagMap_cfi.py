tag_map = {
        # year_era_type
        '2011_X_MC-sigFullSim': 'START42_V14B',
        '2011_X_MC-sigFastSim': 'START42_V14B',
        '2011_X_MC-bg': 'START42_V14B',
        '2011_A_data-PR': 'GR_R_42_V25', # don't use PR tags
        '2011_A_data-RR': 'GR_R_42_V25',
        '2011_B_data-PR': 'GR_R_42_V25', # don't use PR tags
        '2011_B_data-RR': 'GR_R_42_V25',
        '2012_X_MC-bg': 'START53_V7G',
        '2012_X_MC-sigFullSim': 'START53_V7G',
        '2012_X_MC-sigFastSim': 'START53_V7G',
        '2012_A_data-PR': 'FT_53_V6C_AN4',
        '2012_A_data-RR': 'FT_53_V6C_AN4',
        '2012_B_data-PR': 'GR_P_V42_AN4', # FIXME this might be bogus
        '2012_B_data-RR': 'FT_53_V6C_AN4',
        '2012_C_data-PR': 'GR_P_V42_AN4',
        '2012_C_data-RR': 'FT53_V10A_AN4',
        '2012_D_data-PR': 'GR_P_V42_AN4',
        '2012_D_data-RR': ''
        }

def get_tag(s):
    if s in tag_map and tag_map[s] != '':
        return tag_map[s]
    else:
        # FIXME this will actually raise an exception itself
        raise "Can't find a proper tag for " + s
